/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_unmatch.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 14:05:07 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 14:05:09 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int	ft_unmatch(int *tab, int length)
{
	int i;
	int j;
	int is_unique;

	i = 0;
	while (i < length)
	{
		is_unique = 1;
		j = 0;
		while (j < length)
		{
			if (i != j && tab[i] == tab[j])
				is_unique = 0;
			j++;
		}
		if (is_unique)
			return (tab[i]);
		i++;
	}
	return (tab[i]);
}
