/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
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
