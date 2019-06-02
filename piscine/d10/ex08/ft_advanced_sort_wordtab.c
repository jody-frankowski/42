/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_advanced_sort_wordtab.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 14:16:10 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 14:16:10 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

void	ft_sort_strings(char **strings, int (*cmp)(char *, char *))
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
			if (cmp(*search, *min) < 0)
				min = search;
			search++;
		}
		temp = *strings;
		*strings = *min;
		*min = temp;
		strings++;
	}
}

void	ft_advanced_sort_wordtab(char **tab, int (*cmp)(char *, char *))
{
	ft_sort_strings(tab, cmp);
}
