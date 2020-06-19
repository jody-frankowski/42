#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/if_vlan.h>
#include <linux/ip.h>
#include <linux/in.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/types.h>
#include <stdbool.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>

#define likely(x)    __builtin_expect(!!(x), 1)
#define unlikely(x)  __builtin_expect(!!(x), 0)

#ifndef __section
# define __section(NAME)						\
	__attribute__((section(NAME), used))
#endif

#define bpf_printk(fmt, ...)						\
	({												\
		char ____fmt[] = fmt;						\
		bpf_trace_printk(____fmt, sizeof(____fmt),	\
						 ##__VA_ARGS__);			\
	})

// MAX_BW is set deliberately low for the tests
#define MAX_BW 10000
#define ONE_SECOND 1000000000ULL

struct bpf_map_def SEC("maps") scan_bans = {
	.type        = BPF_MAP_TYPE_HASH,
	.key_size    = sizeof(__u32), /* ipv4 */
	.value_size  = sizeof(__u64), /* kernel time in ns */
	.max_entries = 1000000,
	.map_flags   = BPF_F_NO_PREALLOC,
};

struct bandwidth {
	__u32 src_ip;
	__u64 num_packets;
	__u64 update_time;
};

struct bpf_map_def SEC("maps") bandwidth = {
	.type        = BPF_MAP_TYPE_HASH,
	.key_size    = sizeof(__u32), /* ipv4 */
	.value_size  = sizeof(struct bandwidth),
	.max_entries = 1000000,
};

static inline __u32 n32toh32(const __u32 n)
{
	__u32 h = 0;
	int i;

	for (i = 0; i < 4; i++)
		h = h << 8 | ((__u8*)&n)[i];
	return h;
}
static inline __u16 n16toh16(const __u16 n)
{
	__u16 h = 0;
	int i;

	for (i = 0; i < 2; i++)
		h = h << 8 | ((__u8*)&n)[i];
	return h;
}

/*
** Port 53 shouldn't be treated the same way as it is outgoing only.
** Port 80 and 443 are incoming and outgoing.
** Port 9595 is incoming only.
*/

static inline int port_is_whitelisted(__u16 port)
{
	return (port == 53 || port == 80 || port == 443 || port == 9595);
}

/*
** Doesn't care whether it's a TCP or UDP port
*/

static inline int is_scan_banned(__u32 src_ip, __u16 dst_port)
{
	__u64 *ban_time;
	__u64 current_time = bpf_ktime_get_ns();

	if ((ban_time = bpf_map_lookup_elem(&scan_bans, &src_ip)))
	{
		if (current_time - *ban_time > 30 * ONE_SECOND)
		{
			bpf_map_delete_elem(&scan_bans, &src_ip);
		}
		else
		{
			bpf_map_update_elem(&scan_bans, &src_ip, &current_time, BPF_ANY);
			return 1;
		}
	}

	if (!port_is_whitelisted(dst_port))
	{
		bpf_map_update_elem(&scan_bans, &src_ip, &current_time, BPF_ANY);
		return 1;
	}

	return 0;
}

static inline int is_throttled(__u32 src_ip)
{
	struct bandwidth *bw;
	struct bandwidth new_bw = {};
	__u64 current_time = bpf_ktime_get_ns();

	if ((bw = bpf_map_lookup_elem(&bandwidth, &src_ip)))
	{
		if (current_time - bw->update_time > 30 * ONE_SECOND)
		{
			bw->update_time = current_time;
			if (bw->num_packets < MAX_BW)
				bw->num_packets = 0;
			else
				bw->num_packets -= MAX_BW;
		}

		__sync_fetch_and_add(&(bw->num_packets), 1);
	}
	else
	{
		new_bw.src_ip = src_ip;
		new_bw.num_packets = 1;
		new_bw.update_time = current_time;

		bpf_map_update_elem(&bandwidth, &src_ip, &new_bw, BPF_ANY);
		bw = &new_bw;
	}

	return (bw->num_packets > MAX_BW);
}

__section("prog")
int xdp_drop(struct xdp_md *ctx)
{
	void *data = (void *)(long)ctx->data;
	void *data_end = (void *)(long)ctx->data_end;
	struct ethhdr *eth = data;
	__u64 offset = sizeof(*eth);

	if ((void*)(eth + 1) > data_end)
	{
		bpf_printk("eth pointer check abort\n");
		return XDP_ABORTED;
	}

    /* Skip non 802.3 Ethertypes */
    if (unlikely(n16toh16(eth->h_proto) < ETH_P_802_3_MIN))
	{
		bpf_printk("DROP non 802.3 ethernet frames\n");
		return XDP_ABORTED;
	}
    if (unlikely(n16toh16(eth->h_proto) != ETH_P_IP && n16toh16(eth->h_proto) != ETH_P_ARP))
	{
		bpf_printk("DROP ethernet protocol: %x\n", n16toh16(eth->h_proto));
		return XDP_ABORTED;
	}

    if (unlikely(n16toh16(eth->h_proto) == ETH_P_ARP))
	{
		bpf_printk("PASS ARP\n");
		return XDP_PASS;
	}

	struct iphdr *iph = data + offset;
    offset += sizeof(struct iphdr);
    if ((void*)(iph + 1) > data_end)
	{
		bpf_printk("iph pointer check abort\n");
		return XDP_ABORTED;
	}

	__u8 ip_protocol = iph->protocol;
    if (unlikely(ip_protocol != IPPROTO_ICMP &&
				 ip_protocol != IPPROTO_TCP &&
				 ip_protocol != IPPROTO_UDP))
	{
		bpf_printk("DROP IP protocol: %x\n", ip_protocol);
		return XDP_ABORTED;
	}

	__u32 src_ip = iph->saddr;
    if (likely(ip_protocol != IPPROTO_ICMP))
	{
		__u16 src_port;
		__u16 dst_port;
		if (likely(ip_protocol == IPPROTO_TCP))
		{
			struct tcphdr *tcph = data + offset;
			if ((void*)(tcph + 1) > data_end)
			{
				bpf_printk("tcph pointer check abort\n");
				return XDP_ABORTED;
			}

			src_port = tcph->source;
			dst_port = tcph->dest;
		}
		else
		{
			struct tcphdr *udph = data + offset;
			if ((void*)(udph + 1) > data_end)
			{
				bpf_printk("udph pointer check abort\n");
				return XDP_ABORTED;
			}

			src_port = udph->source;
			dst_port = udph->dest;
		}
		src_port = n16toh16(src_port);
		dst_port = n16toh16(dst_port);

		if (unlikely(port_is_whitelisted(src_port) &&
					!port_is_whitelisted(dst_port)))
		{
			bpf_printk("PASS outgoing port: %d\n", src_port);
			return XDP_PASS;
		}

		if (unlikely(is_scan_banned(src_ip, dst_port)))
		{
			bpf_printk("DROP scan banned: %x\n", n32toh32(src_ip));
			bpf_printk("DROP scan banned: port %d\n", dst_port);
			return XDP_ABORTED;
		}
	}

	if (is_throttled(src_ip))
	{
		return XDP_ABORTED;
	}
	else
	{
		return XDP_PASS;
	}
}

char __license[] __section("license") = "GPL";
