/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sqrt.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/01 17:57:40 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 08:55:08 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int sqrt;

	if (nb <= 0)
		return (0);
	sqrt = 1;
	while (sqrt * sqrt < nb && sqrt <= 46340)
		sqrt++;
	if (sqrt * sqrt == nb)
		return (sqrt);
	else
		return (0);
}
