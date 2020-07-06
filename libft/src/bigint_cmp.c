/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_cmp.c                                       :+:      :+:    :+:   */
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
** bigint_cmp() - Compare two bigint
** @op1: The first bigint to compare
** @op2: The second bigint to compare
**
** Return: 1 if op1 > op2. 0 if op1 == op2. -1 if op1 < op2.
*/

int	bigint_cmp(t_bigint op1, t_bigint op2)
{
	size_t last;

	if (op1->sign != op2->sign)
		return (op1->sign == BIGINT_POS ? 1 : -1);
	if (op1->size > op2->size)
		return (op1->sign == BIGINT_POS ? 1 : -1);
	else if (op2->size > op1->size)
		return (op1->sign == BIGINT_POS ? -1 : 1);
	else
	{
		last = op1->size - 1;
		if (op1->val[last] == op2->val[last])
			return (0);
		else if (op1->val[last] > op2->val[last])
			return (op1->sign == BIGINT_POS ? 1 : -1);
		else
			return (op1->sign == BIGINT_POS ? -1 : 1);
	}
}

/*
** bigint_cmpabs() - Compare the absolute value of two bigint
** @op1: The first bigint to compare
** @op2: The second bigint to compare
**
** Return: 1 if abs(op1) > abs(op2). 0 if abs(op1) == abs(op2).
**         -1 if abs(op1) < abs(op2).
*/

int	bigint_cmpabs(t_bigint op1, t_bigint op2)
{
	size_t last;

	if (op1->size > op2->size)
		return (1);
	else if (op2->size > op1->size)
		return (-1);
	else
	{
		last = op1->size - 1;
		return (op1->val[last] - op2->val[last]);
	}
}

/*
** bigint_cmp_si() - Compare a bigint to signed integer
** @op1: The bigint to compare
** @op2: The signed integer bigint to compare
**
** Return: 1 if op1 > op2. 0 if op1 == op2. -1 if op1 < op2.
*/

int	bigint_cmp_si(t_bigint op1, signed long op2)
{
	t_bigint	op2_bigint;
	int			cmp;

	bigint_init(op2_bigint);
	bigint_set_si(op2_bigint, op2);
	cmp = bigint_cmp(op1, op2_bigint);
	bigint_free(op2_bigint);
	return (cmp);
}
