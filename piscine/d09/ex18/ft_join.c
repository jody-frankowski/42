/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_join.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 14:22:16 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 14:22:17 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_len(char **tab)
{
	int len;
	int i;
	int j;

	len = 0;
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			len++;
			j++;
		}
		len++;
		i++;
	}
	return (len);
}

char	*ft_join(char **tab, char *sep)
{
	int		len;
	int		i;
	char	*save;
	char	*result;

	len = ft_len(tab);
	result = (char *)malloc(sizeof(*result) * len);
	if (!result)
		return (result);
	save = result;
	while (*tab)
	{
		i = 0;
		while ((*tab)[i])
		{
			*result = (*tab)[i];
			result++;
			i++;
		}
		*result = *sep;
		result++;
		tab++;
	}
	*(result - 1) = '\0';
	return (save);
}
