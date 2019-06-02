/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 12:14:41 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 12:14:42 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *restrict dst, void *restrict src)
{
	void *restrict save;

	save = dst;
	while (*(char *)src)
		*(char *)dst++ = *(char *)src++;
	*(char *)dst = '\0';
	return (save);
}
