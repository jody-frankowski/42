/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n && *(unsigned char*)src != (unsigned char)c)
	{
		*(unsigned char*)dst = *(unsigned char*)src;
		src = (unsigned char*)src + 1;
		dst = (unsigned char*)dst + 1;
		n--;
	}
	if (n == 0)
		return (NULL);
	else
	{
		*(unsigned char*)dst = *(unsigned char*)src;
		dst = (unsigned char*)dst + 1;
		return (dst);
	}
}
