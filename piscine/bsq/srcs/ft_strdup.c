/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/11 16:38:16 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/11 16:38:19 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*copy;

	len = 0;
	while (src[len])
		len++;
	copy = (char *)malloc(sizeof(*copy) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (src[i])
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strndup(char *src, size_t n)
{
	uint32_t		i;
	int				len;
	char			*copy;

	len = 0;
	while (src[len])
		len++;
	copy = (char *)malloc(sizeof(*copy) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (src[i] && i < n)
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
