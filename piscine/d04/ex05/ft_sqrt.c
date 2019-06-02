/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sqrt.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/06 12:38:48 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/06 12:39:13 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int square;
	int middle;
	int lower;
	int upper;

	if (nb <= 0)
		return (0);
	if (nb == 1)
		return (1);
	lower = 2;
	upper = nb / 2 > 46340 ? 46340 : nb / 2;
	while (lower <= upper)
	{
		middle = lower + (upper - lower) / 2;
		square = middle * middle;
		if (square < nb)
			lower = middle + 1;
		else if (square > nb)
			upper = middle - 1;
		else
			return (middle);
	}
	return (0);
}
