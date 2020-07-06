/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errno.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERRNO_H
# define FT_ERRNO_H

# define FT_NERR 135

/*
** Stolen from a Linux machine
*/
# define FT_SUCCESS 0
# define FT_SUCCESS_STR "Success"
# define FT_EPERM 1
# define FT_EPERM_STR "Operation not permitted"
# define FT_ENOENT 2
# define FT_ENOENT_STR "No such file or directory"
# define FT_ESRCH 3
# define FT_ESRCH_STR "No such process"
# define FT_EINTR 4
# define FT_EINTR_STR "Interrupted system call"
# define FT_EIO 5
# define FT_EIO_STR "I/O error"
# define FT_ENXIO 6
# define FT_ENXIO_STR "No such device or address"
# define FT_E2BIG 7
# define FT_E2BIG_STR "Argument list too long"
# define FT_ENOEXEC 8
# define FT_ENOEXEC_STR "Exec format error"
# define FT_EBADF 9
# define FT_EBADF_STR "Bad file number"
# define FT_ECHILD 10
# define FT_ECHILD_STR "No child processes"
# define FT_EAGAIN 11
# define FT_EAGAIN_STR "Try again"
# define FT_ENOMEM 12
# define FT_ENOMEM_STR "Out of memory"
# define FT_EACCES 13
# define FT_EACCES_STR "Permission denied"
# define FT_EFAULT 14
# define FT_EFAULT_STR "Bad address"
# define FT_ENOTBLK 15
# define FT_ENOTBLK_STR "Block device required"
# define FT_EBUSY 16
# define FT_EBUSY_STR "Device or resource busy"
# define FT_EEXIST 17
# define FT_EEXIST_STR "File exists"
# define FT_EXDEV 18
# define FT_EXDEV_STR "Cross-device link"
# define FT_ENODEV 19
# define FT_ENODEV_STR "No such device"
# define FT_ENOTDIR 20
# define FT_ENOTDIR_STR "Not a directory"
# define FT_EISDIR 21
# define FT_EISDIR_STR "Is a directory"
# define FT_EINVAL 22
# define FT_EINVAL_STR "Invalid argument"
# define FT_ENFILE 23
# define FT_ENFILE_STR "File table overflow"
# define FT_EMFILE 24
# define FT_EMFILE_STR "Too many open files"
# define FT_ENOTTY 25
# define FT_ENOTTY_STR "Not a typewriter"
# define FT_ETXTBSY 26
# define FT_ETXTBSY_STR "Text file busy"
# define FT_EFBIG 27
# define FT_EFBIG_STR "File too large"
# define FT_ENOSPC 28
# define FT_ENOSPC_STR "No space left on device"
# define FT_ESPIPE 29
# define FT_ESPIPE_STR "Illegal seek"
# define FT_EROFS 30
# define FT_EROFS_STR "Read-only file system"
# define FT_EMLINK 31
# define FT_EMLINK_STR "Too many links"
# define FT_EPIPE 32
# define FT_EPIPE_STR "Broken pipe"
# define FT_EDOM 33
# define FT_EDOM_STR "Math argument out of domain of func"
# define FT_ERANGE 34
# define FT_ERANGE_STR "Math result not representable"
# define FT_EDEADLK 35
# define FT_EDEADLK_STR "Resource deadlock would occur"
# define FT_ENAMETOOLONG 36
# define FT_ENAMETOOLONG_STR "File name too long"
# define FT_ENOLCK 37
# define FT_ENOLCK_STR "No record locks available"
# define FT_ENOSYS 38
# define FT_ENOSYS_STR "Invalid system call number"
# define FT_ENOTEMPTY 39
# define FT_ENOTEMPTY_STR "Directory not empty"
# define FT_ELOOP 40
# define FT_ELOOP_STR "Too many symbolic links encountered"
# define FT_EWOULDBLOCK EAGAIN
# define FT_EWOULDBLOCK_STR "Operation would block"
# define FT_ENOMSG 42
# define FT_ENOMSG_STR "No message of desired type"
# define FT_EIDRM 43
# define FT_EIDRM_STR "Identifier removed"
# define FT_ECHRNG 44
# define FT_ECHRNG_STR "Channel number out of range"
# define FT_EL2NSYNC 45
# define FT_EL2NSYNC_STR "Level 2 not synchronized"
# define FT_EL3HLT 46
# define FT_EL3HLT_STR "Level 3 halted"
# define FT_EL3RST 47
# define FT_EL3RST_STR "Level 3 reset"
# define FT_ELNRNG 48
# define FT_ELNRNG_STR "Link number out of range"
# define FT_EUNATCH 49
# define FT_EUNATCH_STR "Protocol driver not attached"
# define FT_ENOCSI 50
# define FT_ENOCSI_STR "No CSI structure available"
# define FT_EL2HLT 51
# define FT_EL2HLT_STR "Level 2 halted"
# define FT_EBADE 52
# define FT_EBADE_STR "Invalid exchange"
# define FT_EBADR 53
# define FT_EBADR_STR "Invalid request descriptor"
# define FT_EXFULL 54
# define FT_EXFULL_STR "Exchange full"
# define FT_ENOANO 55
# define FT_ENOANO_STR "No anode"
# define FT_EBADRQC 56
# define FT_EBADRQC_STR "Invalid request code"
# define FT_EBADSLT 57
# define FT_EBADSLT_STR "Invalid slot"
# define FT_EDEADLOCK FT_EDEADLK
# define FT_EDEADLOCK_STR FT_EDEADLK_STR
# define FT_EBFONT 59
# define FT_EBFONT_STR "Bad font file format"
# define FT_ENOSTR 60
# define FT_ENOSTR_STR "Device not a stream"
# define FT_ENODATA 61
# define FT_ENODATA_STR "No data available"
# define FT_ETIME 62
# define FT_ETIME_STR "Timer expired"
# define FT_ENOSR 63
# define FT_ENOSR_STR "Out of streams resources"
# define FT_ENONET 64
# define FT_ENONET_STR "Machine is not on the network"
# define FT_ENOPKG 65
# define FT_ENOPKG_STR "Package not installed"
# define FT_EREMOTE 66
# define FT_EREMOTE_STR "Object is remote"
# define FT_ENOLINK 67
# define FT_ENOLINK_STR "Link has been severed"
# define FT_EADV 68
# define FT_EADV_STR "Advertise error"
# define FT_ESRMNT 69
# define FT_ESRMNT_STR "Srmount error"
# define FT_ECOMM 70
# define FT_ECOMM_STR "Communication error on send"
# define FT_EPROTO 71
# define FT_EPROTO_STR "Protocol error"
# define FT_EMULTIHOP 72
# define FT_EMULTIHOP_STR "Multihop attempted"
# define FT_EDOTDOT 73
# define FT_EDOTDOT_STR "RFS specific error"
# define FT_EBADMSG 74
# define FT_EBADMSG_STR "Not a data message"
# define FT_EOVERFLOW 75
# define FT_EOVERFLOW_STR "Value too large for defined data type"
# define FT_ENOTUNIQ 76
# define FT_ENOTUNIQ_STR "Name not unique on network"
# define FT_EBADFD 77
# define FT_EBADFD_STR "File descriptor in bad state"
# define FT_EREMCHG 78
# define FT_EREMCHG_STR "Remote address changed"
# define FT_ELIBACC 79
# define FT_ELIBACC_STR "Can not access a needed shared library"
# define FT_ELIBBAD 80
# define FT_ELIBBAD_STR "Accessing a corrupted shared library"
# define FT_ELIBSCN 81
# define FT_ELIBSCN_STR ".lib section in a.out corrupted"
# define FT_ELIBMAX 82
# define FT_ELIBMAX_STR "Attempting to link in too many shared libraries"
# define FT_ELIBEXEC 83
# define FT_ELIBEXEC_STR "Cannot exec a shared library directly"
# define FT_EILSEQ 84
# define FT_EILSEQ_STR "Illegal byte sequence"
# define FT_ERESTART 85
# define FT_ERESTART_STR "Interrupted system call should be restarted"
# define FT_ESTRPIPE 86
# define FT_ESTRPIPE_STR "Streams pipe error"
# define FT_EUSERS 87
# define FT_EUSERS_STR "Too many users"
# define FT_ENOTSOCK 88
# define FT_ENOTSOCK_STR "Socket operation on non-socket"
# define FT_EDESTADDRREQ 89
# define FT_EDESTADDRREQ_STR "Destination address required"
# define FT_EMSGSIZE 90
# define FT_EMSGSIZE_STR "Message too long"
# define FT_EPROTOTYPE 91
# define FT_EPROTOTYPE_STR "Protocol wrong type for socket"
# define FT_ENOPROTOOPT 92
# define FT_ENOPROTOOPT_STR "Protocol not available"
# define FT_EPROTONOSUPPORT 93
# define FT_EPROTONOSUPPORT_STR "Protocol not supported"
# define FT_ESOCKTNOSUPPORT 94
# define FT_ESOCKTNOSUPPORT_STR "Socket type not supported"
# define FT_EOPNOTSUPP 95
# define FT_EOPNOTSUPP_STR "Operation not supported on transport endpoint"
# define FT_EPFNOSUPPORT 96
# define FT_EPFNOSUPPORT_STR "Protocol family not supported"
# define FT_EAFNOSUPPORT 97
# define FT_EAFNOSUPPORT_STR "Address family not supported by protocol"
# define FT_EADDRINUSE 98
# define FT_EADDRINUSE_STR "Address already in use"
# define FT_EADDRNOTAVAIL 99
# define FT_EADDRNOTAVAIL_STR "Cannot assign requested address"
# define FT_ENETDOWN 100
# define FT_ENETDOWN_STR "Network is down"
# define FT_ENETUNREACH 101
# define FT_ENETUNREACH_STR "Network is unreachable"
# define FT_ENETRESET 102
# define FT_ENETRESET_STR "Network dropped connection because of reset"
# define FT_ECONNABORTED 103
# define FT_ECONNABORTED_STR "Software caused connection abort"
# define FT_ECONNRESET 104
# define FT_ECONNRESET_STR "Connection reset by peer"
# define FT_ENOBUFS 105
# define FT_ENOBUFS_STR "No buffer space available"
# define FT_EISCONN 106
# define FT_EISCONN_STR "Transport endpoint is already connected"
# define FT_ENOTCONN 107
# define FT_ENOTCONN_STR "Transport endpoint is not connected"
# define FT_ESHUTDOWN 108
# define FT_ESHUTDOWN_STR "Cannot send after transport endpoint shutdown"
# define FT_ETOOMANYREFS 109
# define FT_ETOOMANYREFS_STR "Too many references: cannot splice"
# define FT_ETIMEDOUT 110
# define FT_ETIMEDOUT_STR "Connection timed out"
# define FT_ECONNREFUSED 111
# define FT_ECONNREFUSED_STR "Connection refused"
# define FT_EHOSTDOWN 112
# define FT_EHOSTDOWN_STR "Host is down"
# define FT_EHOSTUNREACH 113
# define FT_EHOSTUNREACH_STR "No route to host"
# define FT_EALREADY 114
# define FT_EALREADY_STR "Operation already in progress"
# define FT_EINPROGRESS 115
# define FT_EINPROGRESS_STR "Operation now in progress"
# define FT_ESTALE 116
# define FT_ESTALE_STR "Stale file handle"
# define FT_EUCLEAN 117
# define FT_EUCLEAN_STR "Structure needs cleaning"
# define FT_ENOTNAM 118
# define FT_ENOTNAM_STR "Not a XENIX named type file"
# define FT_ENAVAIL 119
# define FT_ENAVAIL_STR "No XENIX semaphores available"
# define FT_EISNAM 120
# define FT_EISNAM_STR "Is a named type file"
# define FT_EREMOTEIO 121
# define FT_EREMOTEIO_STR "Remote I/O error"
# define FT_EDQUOT 122
# define FT_EDQUOT_STR "Quota exceeded"
# define FT_ENOMEDIUM 123
# define FT_ENOMEDIUM_STR "No medium found"
# define FT_EMEDIUMTYPE 124
# define FT_EMEDIUMTYPE_STR "Wrong medium type"
# define FT_ECANCELED 125
# define FT_ECANCELED_STR "Operation Canceled"
# define FT_ENOKEY 126
# define FT_ENOKEY_STR "Required key not available"
# define FT_EKEYEXPIRED 127
# define FT_EKEYEXPIRED_STR "Key has expired"
# define FT_EKEYREVOKED 128
# define FT_EKEYREVOKED_STR "Key has been revoked"
# define FT_EKEYREJECTED 129
# define FT_EKEYREJECTED_STR "Key was rejected by service"
# define FT_EOWNERDEAD 130
# define FT_EOWNERDEAD_STR "Owner died"
# define FT_ENOTRECOVERABLE 131
# define FT_ENOTRECOVERABLE_STR "State not recoverable"
# define FT_ERFKILL 132
# define FT_ERFKILL_STR "Operation not possible due to RF-kill"
# define FT_EHWPOISON 133
# define FT_EHWPOISON_STR "Memory page has hardware error"

/*
** These two variables are not specified by POSIX, and are nowadays deprecated
** on systems that implemented them, but I think they are good enough for our
** needs.
*/
int	g_ft_sys_nerr = FT_NERR;
char	*g_ft_sys_errlist[FT_NERR] = {
	FT_SUCCESS_STR,
	FT_EPERM_STR,
	FT_ENOENT_STR,
	FT_ESRCH_STR,
	FT_EINTR_STR,
	FT_EIO_STR,
	FT_ENXIO_STR,
	FT_E2BIG_STR,
	FT_ENOEXEC_STR,
	FT_EBADF_STR,
	FT_ECHILD_STR,
	FT_EAGAIN_STR,
	FT_ENOMEM_STR,
	FT_EACCES_STR,
	FT_EFAULT_STR,
	FT_ENOTBLK_STR,
	FT_EBUSY_STR,
	FT_EEXIST_STR,
	FT_EXDEV_STR,
	FT_ENODEV_STR,
	FT_ENOTDIR_STR,
	FT_EISDIR_STR,
	FT_EINVAL_STR,
	FT_ENFILE_STR,
	FT_EMFILE_STR,
	FT_ENOTTY_STR,
	FT_ETXTBSY_STR,
	FT_EFBIG_STR,
	FT_ENOSPC_STR,
	FT_ESPIPE_STR,
	FT_EROFS_STR,
	FT_EMLINK_STR,
	FT_EPIPE_STR,
	FT_EDOM_STR,
	FT_ERANGE_STR,
	FT_EDEADLK_STR,
	FT_ENAMETOOLONG_STR,
	FT_ENOLCK_STR,
	FT_ENOSYS_STR,
	FT_ENOTEMPTY_STR,
	FT_ELOOP_STR,
	FT_EWOULDBLOCK_STR,
	FT_ENOMSG_STR,
	FT_EIDRM_STR,
	FT_ECHRNG_STR,
	FT_EL2NSYNC_STR,
	FT_EL3HLT_STR,
	FT_EL3RST_STR,
	FT_ELNRNG_STR,
	FT_EUNATCH_STR,
	FT_ENOCSI_STR,
	FT_EL2HLT_STR,
	FT_EBADE_STR,
	FT_EBADR_STR,
	FT_EXFULL_STR,
	FT_ENOANO_STR,
	FT_EBADRQC_STR,
	FT_EBADSLT_STR,
	FT_EDEADLOCK_STR,
	FT_EBFONT_STR,
	FT_ENOSTR_STR,
	FT_ENODATA_STR,
	FT_ETIME_STR,
	FT_ENOSR_STR,
	FT_ENONET_STR,
	FT_ENOPKG_STR,
	FT_EREMOTE_STR,
	FT_ENOLINK_STR,
	FT_EADV_STR,
	FT_ESRMNT_STR,
	FT_ECOMM_STR,
	FT_EPROTO_STR,
	FT_EMULTIHOP_STR,
	FT_EDOTDOT_STR,
	FT_EBADMSG_STR,
	FT_EOVERFLOW_STR,
	FT_ENOTUNIQ_STR,
	FT_EBADFD_STR,
	FT_EREMCHG_STR,
	FT_ELIBACC_STR,
	FT_ELIBBAD_STR,
	FT_ELIBSCN_STR,
	FT_ELIBMAX_STR,
	FT_ELIBEXEC_STR,
	FT_EILSEQ_STR,
	FT_ERESTART_STR,
	FT_ESTRPIPE_STR,
	FT_EUSERS_STR,
	FT_ENOTSOCK_STR,
	FT_EDESTADDRREQ_STR,
	FT_EMSGSIZE_STR,
	FT_EPROTOTYPE_STR,
	FT_ENOPROTOOPT_STR,
	FT_EPROTONOSUPPORT_STR,
	FT_ESOCKTNOSUPPORT_STR,
	FT_EOPNOTSUPP_STR,
	FT_EPFNOSUPPORT_STR,
	FT_EAFNOSUPPORT_STR,
	FT_EADDRINUSE_STR,
	FT_EADDRNOTAVAIL_STR,
	FT_ENETDOWN_STR,
	FT_ENETUNREACH_STR,
	FT_ENETRESET_STR,
	FT_ECONNABORTED_STR,
	FT_ECONNRESET_STR,
	FT_ENOBUFS_STR,
	FT_EISCONN_STR,
	FT_ENOTCONN_STR,
	FT_ESHUTDOWN_STR,
	FT_ETOOMANYREFS_STR,
	FT_ETIMEDOUT_STR,
	FT_ECONNREFUSED_STR,
	FT_EHOSTDOWN_STR,
	FT_EHOSTUNREACH_STR,
	FT_EALREADY_STR,
	FT_EINPROGRESS_STR,
	FT_ESTALE_STR,
	FT_EUCLEAN_STR,
	FT_ENOTNAM_STR,
	FT_ENAVAIL_STR,
	FT_EISNAM_STR,
	FT_EREMOTEIO_STR,
	FT_EDQUOT_STR,
	FT_ENOMEDIUM_STR,
	FT_EMEDIUMTYPE_STR,
	FT_ECANCELED_STR,
	FT_ENOKEY_STR,
	FT_EKEYEXPIRED_STR,
	FT_EKEYREVOKED_STR,
	FT_EKEYREJECTED_STR,
	FT_EOWNERDEAD_STR,
	FT_ENOTRECOVERABLE_STR,
	FT_ERFKILL_STR,
	FT_EHWPOISON_STR,
};

int	g_errno;

#endif
