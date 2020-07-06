/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_bits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "bigint.h"

/*
** bigint_get_bit() - Get a bit from a bigint
** @num: The bigint from which to extract the bit
** @n:   Which bit to get starting from 0
**
** /!\ This function doesn't check whether n is smaller than the number of bits
** of num!
**
** Return: 1 or 0 depending on the bit value.
*/

int		bigint_get_bit(t_bigint num, size_t n)
{
	size_t val_n;

	val_n = (n / BIGINT_VAL_NBIT);
	return (1 & (num->val[val_n] >> (n % BIGINT_VAL_NBIT)));
}

/*
** bigint_set_bit() - Set a bit from a bigint
** @num: The bigint from which to set the bit
** @n:   Which bit to set starting from 0
** @val: The value of the bit to set
**
** /!\ This function doesn't check whether n is smaller than the number of bits
** of num!
** /!\ This function doesn't check whether val is equal to 0 or 1 only!
*/

void	bigint_set_bit(t_bigint num, size_t n, unsigned char val)
{
	size_t val_n;

	val_n = (n / BIGINT_VAL_NBIT);
	num->val[val_n] = (num->val[val_n] & 1 << (n % BIGINT_VAL_NBIT)) \
		| val << (n % BIGINT_VAL_NBIT);
}

/*
** bigint_shift_left() - Shift a bigint to the left once
** @res: The resulft of the shift
** @op1: The bigint to shift left
**
** @res can point to the same bigint as @op1.
**
** Return: 1 on success. 0 on error.
*/

int		bigint_shift_left(t_bigint res, t_bigint op1)
{
	int i;

	i = op1->size - 1;
	if (op1->val[i] >> (BIGINT_VAL_NBIT - 1) == 1)
	{
		if (!(bigint_realloc(res, op1->size + 1)))
			return (0);
		res->val[i + 1] = 1;
	}
	else
	{
		if (!(bigint_realloc(res, op1->size)))
			return (0);
	}
	while (i != -1)
	{
		res->val[i] = op1->val[i] << 1;
		if (i >= 1)
			res->val[i] |= op1->val[i - 1] >> (BIGINT_VAL_NBIT - 1);
		i--;
	}
	return (1);
}

/*
** bigint_num_bits() - Get the number of bits of a bigint
** @num: The bigint whose bits to count
**
** Return: The number of bits of @num.
*/

size_t	bigint_num_bits(t_bigint num)
{
	size_t			num_bits;
	t_bigint_val	val;

	num_bits = (num->size - 1) * BIGINT_VAL_NBIT;
	val = num->val[num->size - 1];
	while (val)
	{
		val = val >> 1;
		num_bits++;
	}
	return (num_bits);
}
