/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 18:20:27 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 18:20:27 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
