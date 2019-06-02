/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sort_wordtab.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 12:14:26 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 12:14:27 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int		ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	ft_sort_strings(char **strings)
{
	char	**min;
	char	*temp;
	char	**search;

	while (*strings)
	{
		min = strings;
		search = strings;
		while (*search)
		{
			if (ft_strcmp(*search, *min) < 0)
			{
				min = search;
			}
			search++;
		}
		temp = *strings;
		*strings = *min;
		*min = temp;
		strings++;
	}
}

void	ft_sort_wordtab(char **tab)
{
	ft_sort_strings(tab);
}
