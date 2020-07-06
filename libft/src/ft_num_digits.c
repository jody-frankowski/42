/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_digits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

/*
** ft_num_digits - Counts the number of base 10 digits in an integer
** @n: The integer in which to count the number of base 10 digits
**
** Return: The number of digits in n
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

/*
** ft_num_digits_ll - Counts the number of digits in a specific base in a
**                    long long
** @num:  The integer in which to count the number of digits
** @base: The base to consider
**
** Return: The number of digits
*/

size_t	ft_num_digits_ll(long long num, int base)
{
	size_t num_digits;

	if (num == 0)
		return (1);
	num_digits = 0;
	while (num)
	{
		num /= base;
		num_digits++;
	}
	return (num_digits);
}

/*
** ft_num_digits_ull - Counts the number of digits in a specific base in a
**                     unsigned long long
** @num:  The integer in which to count the number of digits
** @base: The base to consider
**
** Return: The number of digits
*/

size_t	ft_num_digits_ull(unsigned long long num, int base)
{
	size_t num_digits;

	if (num == 0)
		return (1);
	num_digits = 0;
	while (num)
	{
		num /= base;
		num_digits++;
	}
	return (num_digits);
}
