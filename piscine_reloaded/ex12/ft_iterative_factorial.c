/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_iterative_factorial.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 17:22:16 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/01 17:47:26 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int factorial;
	int old;

	factorial = 1;
	if (nb < 0)
		return (0);
	while (nb > 0)
	{
		old = factorial;
		factorial *= nb;
		if (factorial / nb != old)
			return (0);
		nb--;
	}
	return (factorial);
}
