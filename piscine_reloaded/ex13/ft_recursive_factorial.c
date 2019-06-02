/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_recursive_factorial.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 17:43:54 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/01 17:56:34 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int	ft_recursive_factorial(int nb)
{
	int factorial;

	if (nb < 0)
		return (0);
	if (nb == 0 || nb == 1)
		return (1);
	factorial = nb * ft_recursive_factorial(nb - 1);
	if (factorial / nb != ft_recursive_factorial(nb - 1))
		return (0);
	return (factorial);
}
