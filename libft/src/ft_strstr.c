/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 14:59:41 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 14:59:41 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
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
		while (needle[j] && needle[j] == haystack[i])
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
