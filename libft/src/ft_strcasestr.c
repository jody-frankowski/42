/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcasestr.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 16:24:01 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 16:24:01 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strcasestr(const char *haystack, const char *needle)
{
	size_t i;
	size_t j;
	size_t save_i;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		save_i = i;
		while (needle[j] && ft_charcasecmp(needle[j], haystack[i]) == 0)
		{
			i++;
			j++;
		}
		if (!needle[j])
			return ((char *)haystack + save_i);
		i = save_i;
		i++;
	}
	return (NULL);
}
