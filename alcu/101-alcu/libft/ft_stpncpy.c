/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_stpncpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 17:06:01 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 17:06:01 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>

char	*ft_stpncpy(char *dst, const char *src, size_t len)
{
	char *save;

	while (*src && len)
	{
		*dst++ = *src++;
		len--;
	}
	save = dst;
	while (len)
	{
		*dst++ = '\0';
		len--;
	}
	return (save);
}
