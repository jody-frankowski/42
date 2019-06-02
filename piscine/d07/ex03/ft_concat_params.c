/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_concat_params.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/11 22:15:47 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/11 22:16:01 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_params_len(int argc, char **argv)
{
	int i;
	int j;
	int len;

	i = 0;
	len = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			len++;
			j++;
		}
		len++;
		i++;
	}
	return (len);
}

char	*ft_concat_params(int argc, char **argv)
{
	int		i;
	int		j;
	int		k;
	char	*params;

	params = (char *)malloc(sizeof(params) * (ft_params_len(argc, argv) + 1));
	if (!params)
		return (NULL);
	i = 0;
	k = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			params[k] = argv[i][j];
			j++;
			k++;
		}
		params[k] = '\n';
		k++;
		i++;
	}
	params[k - 1] = '\0';
	return (params);
}
