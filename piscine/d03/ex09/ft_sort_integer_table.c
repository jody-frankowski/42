/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sort_integer_table.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 14:02:56 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 14:02:57 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

void	ft_swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_sort_integer_table(int *tab, int size)
{
	int *min;
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = i;
		min = &tab[i];
		while (j < size)
		{
			if (tab[j] < *min)
			{
				min = &tab[j];
			}
			j++;
		}
		ft_swap(&tab[i], min);
		i++;
	}
}
