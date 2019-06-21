/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: husahuc <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 10:51:54 by husahuc      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 10:58:55 by husahuc     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdint.h>

int	keycmp(const char *key1, const char *key2, uint8_t key1_len)
{
	while (key1_len >= 8 && *(uint64_t*)key1 == *(uint64_t*)key2)
	{
		key1 += 8;
		key2 += 8;
		key1_len -= 8;
	}
	while (key1_len >= 4 && *(uint32_t*)key1 == *(uint32_t*)key2)
	{
		key1 += 4;
		key2 += 4;
		key1_len -= 4;
	}
	while (key1_len && *key1 == *key2)
	{
		key1++;
		key2++;
		key1_len--;
	}
	if (*key2 & 0b10000000)
		return (0);
	else
		return (1);
}
