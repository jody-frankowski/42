/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_add_sub.c                                   :+:      :+:    :+:   */
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
** bigint_add_abs() - Add the absolute value of two bigint together
** @res: The result of the addition
** @op1: The first bigint to add
** @op2: The second bigint to add
**
** Return: 1 on success. 0 on error.
*/

int	bigint_add_abs(t_bigint res, t_bigint op1, t_bigint op2)
{
	t_bigint_val	op1_val;
	t_bigint_val	op2_val;
	unsigned int	carry;
	unsigned int	new_carry;
	size_t			i;

	carry = 0;
	i = 0;
	while (carry || i < op1->size || i < op2->size)
	{
		if (i >= res->size)
			if (!(bigint_alloc_one_more(res)))
				return (0);
		op1_val = i < op1->size ? op1->val[i] : 0;
		op2_val = i < op2->size ? op2->val[i] : 0;
		res->val[i] = op1_val;
		new_carry = 0;
		if (BIGINT_MAX - op2_val < res->val[i])
			new_carry = 1;
		res->val[i] += op2_val + carry;
		carry = new_carry;
		i++;
	}
	res->size = i;
	return (1);
}

/*
** bigint_sub_abs() - Subtract the absolute value of a bigint from another
** @res: The result of the subtraction
** @op1: The bigint to subtract from
** @op2: The bigint to subtract to
**
** /!\ op1 MUST be bigger or equal to op2.
**
** Return: 1 on success. 0 on error.
*/

int	bigint_sub_abs(t_bigint res, t_bigint op1, t_bigint op2)
{
	t_bigint_val	op1_val;
	t_bigint_val	op2_val;
	unsigned int	carry;
	unsigned int	new_carry;
	size_t			i;

	carry = 0;
	i = 0;
	while (carry || i < op1->size || i < op2->size)
	{
		if (i >= res->size)
			if (!(bigint_alloc_one_more(res)))
				return (0);
		op1_val = i < op1->size ? op1->val[i] : 0;
		op2_val = i < op2->size ? op2->val[i] : 0;
		res->val[i] = op1_val;
		new_carry = 0;
		if (op2_val > op1_val)
			new_carry = 1;
		res->val[i] -= (op2_val + carry);
		carry = new_carry;
		i++;
	}
	bigint_fix_size(res);
	return (1);
}

/*
** bigint_add() - Add two bigint together
** @res: The result of the addition
** @op1: The first bigint to add
** @op2: The second bigint to add
**
** @res can point to the same bigint as @op1 or @op2 or even both.
** We use the lower level functions add_abs and sub_ads and the following rules:
** + + + = add & +
** - + - = add & -
** + + - = sub & (+ if 1st >= 2nd, else -)
** - + + = sub & (- if 1st >  2nd, else +)
**
** Return: 1 on success. 0 on error.
*/

int	bigint_add(t_bigint res, t_bigint op1, t_bigint op2)
{
	if (op1->sign == BIGINT_POS && op2->sign == BIGINT_POS)
	{
		res->sign = BIGINT_POS;
		return (bigint_add_abs(res, op1, op2));
	}
	else if (op1->sign == BIGINT_NEG && op2->sign == BIGINT_NEG)
	{
		res->sign = BIGINT_NEG;
		return (bigint_add_abs(res, op1, op2));
	}
	else if (op1->sign == BIGINT_POS && op2->sign == BIGINT_NEG)
		return (bigint_sub_pos_neg(res, op1, op2));
	else
		return (bigint_sub_neg_pos(res, op1, op2));
}

/*
** bigint_sub() - Subtract the a bigint from another
** @res: The result of the subtraction
** @op1: The bigint to subtract from
** @op2: The bigint to subtract to
**
** @res can point to the same bigint as @op1 or @op2 or even both.
** We use the lower level functions add_abs and sub_ads and the following rules:
** + - + = sub & (+ if 1st >= 2nd, else -)
** - - - = sub & (- if 1st >  2nd, else +)
** + - - = add & +
** - - + = add & -
**
** Return: 1 on success. 0 on error.
*/

int	bigint_sub(t_bigint res, t_bigint op1, t_bigint op2)
{
	if (op1->sign == BIGINT_POS && op2->sign == BIGINT_POS)
		return (bigint_sub_pos_neg(res, op1, op2));
	else if (op1->sign == BIGINT_NEG && op2->sign == BIGINT_NEG)
		return (bigint_sub_neg_pos(res, op1, op2));
	else if (op1->sign == BIGINT_POS && op2->sign == BIGINT_NEG)
	{
		res->sign = BIGINT_POS;
		return (bigint_add_abs(res, op1, op2));
	}
	else
	{
		res->sign = BIGINT_NEG;
		return (bigint_add_abs(res, op1, op2));
	}
}
