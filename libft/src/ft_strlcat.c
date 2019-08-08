/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 13:02:18 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 13:02:18 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t dest_len;
	size_t src_len;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size == 0)
		return (dest_len < size ? dest_len + src_len : size + src_len);
	dst += dest_len;
	if (dest_len <= size)
		ft_strlcpy(dst, src, size - dest_len);
	return (dest_len < size ? dest_len + src_len : size + src_len);
}
