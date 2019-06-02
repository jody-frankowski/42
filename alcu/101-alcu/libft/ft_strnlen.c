/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnlen.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 17:11:04 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 17:11:04 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t len;

	len = 0;
	while (*s++ && maxlen--)
		len++;
	return (len);
}
