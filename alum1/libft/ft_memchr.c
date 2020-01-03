/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 18:20:08 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 18:20:08 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n && *(unsigned char*)s != (unsigned char)c)
	{
		s++;
		n--;
	}
	if (n == 0)
		return (NULL);
	else
		return ((void*)s);
}
