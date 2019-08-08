/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 14:21:07 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 14:21:07 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t len;

	if (size == 0)
		return (ft_strlen(src));
	len = 0;
	while (len < size - 1 && *src)
	{
		*dst++ = *src++;
		len++;
	}
	if (len < size)
		*dst = '\0';
	while (*src)
	{
		src++;
		len++;
	}
	return (len);
}
