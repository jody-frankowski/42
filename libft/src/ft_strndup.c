/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strndup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 17:13:06 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 17:13:06 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*dup;
	size_t	len;

	len = ft_strnlen(s1, n);
	if (!(dup = malloc(sizeof(*s1) * (len + 1))))
		return (NULL);
	*ft_stpncpy(dup, s1, len) = '\0';
	return (dup);
}
