/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_param_to_tab.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 22:56:50 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 22:56:52 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_stock_par.h"

char				**ft_split_whitespaces(char *str);

int					ft_strlen(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

char				*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*copy;

	len = 0;
	while (src[len])
		len++;
	copy = (char *)malloc(sizeof(*copy) * (len + 1));
	if (!copy)
		return (copy);
	i = 0;
	while (src[i])
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

struct s_stock_par	*ft_param_to_tab(int ac, char **av)
{
	t_stock_par	*result;
	int			i;

	result = (t_stock_par *)malloc(sizeof(*result) * (ac + 1));
	if (!result)
		return (result);
	i = 0;
	while (i < ac)
	{
		result[i].size_param = ft_strlen(av[i]);
		result[i].str = av[i];
		result[i].copy = ft_strdup(av[i]);
		result[i].tab = ft_split_whitespaces(av[i]);
		i++;
	}
	result[i].str = (NULL);
	return (result);
}
