/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_pow.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 18:32:11 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 18:32:11 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/*
** ft_pow - Exponentiate a number
** @base: The number to exponentiate
** @exponent: The exponent to use
**
** If @exponent is negative, the behavior is undefined.
**
** Return: @base to the power of @exponent
*/

int	ft_pow(int base, int exponent)
{
	int i;
	int result;

	if (exponent == 0)
		return (1);
	i = 1;
	result = base;
	while (i < exponent)
	{
		result *= base;
		i++;
	}
	return (result);
}
