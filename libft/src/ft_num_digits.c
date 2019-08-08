/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_num_digits.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 18:21:54 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 18:21:54 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>

/*
** Returns the number of digits in n.
*/

size_t	ft_num_digits(int n)
{
	int		num_digits;

	if (n == 0)
		return (1);
	num_digits = 0;
	while (n)
	{
		n /= 10;
		num_digits++;
	}
	return (num_digits);
}
