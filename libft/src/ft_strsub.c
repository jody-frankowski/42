/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsub.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/07 17:26:05 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 17:26:05 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *sub;
	char *save;

	if (!s)
		return (NULL);
	if (!(sub = malloc(sizeof(*s) * (len + 1))))
		return (NULL);
	save = sub;
	s += start;
	while (len--)
		*sub++ = *s++;
	*sub = 0;
	return (save);
}
