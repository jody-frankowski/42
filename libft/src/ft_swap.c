/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

/*
** ft_swap - Swap the content of two buffers in-place
** @a: A buffer
** @b: A buffer
** @len: The length of the swap in bytes
**
** Swaps the content pointed by a with the content pointed by b.
** The swap is done in place with XOR, so no malloc is needed.
** The XOR is done on elements of `long` size as long as possible.
** TODO Handle a and b being misaligned.
** /!\ if a == b, the buffer will be cleared out (set to zeroes).
*/

void	ft_swap(void *a, void *b, size_t len)
{
	while (len > WORDSIZE)
	{
		*(t_word *)a ^= *(t_word *)b;
		*(t_word *)b ^= *(t_word *)a;
		*(t_word *)a ^= *(t_word *)b;
		a += WORDSIZE;
		b += WORDSIZE;
		len -= WORDSIZE;
	}
	while (len--)
	{
		*(char *)a ^= *(char *)b;
		*(char *)b ^= *(char *)a;
		*(char *)a ^= *(char *)b;
		a++;
		b++;
	}
}
