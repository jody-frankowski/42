/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_add_sub_norm.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

int	bigint_sub_pos_neg(t_bigint res, t_bigint op1, t_bigint op2)
{
	int cmp;

	cmp = bigint_cmpabs(op1, op2);
	if (cmp == 0)
	{
		bigint_set_ui(res, 0);
		return (1);
	}
	else if (cmp > 0)
	{
		res->sign = BIGINT_POS;
		return (bigint_sub_abs(res, op1, op2));
	}
	else
	{
		res->sign = BIGINT_NEG;
		return (bigint_sub_abs(res, op2, op1));
	}
}

int	bigint_sub_neg_pos(t_bigint res, t_bigint op1, t_bigint op2)
{
	int cmp;

	cmp = bigint_cmpabs(op1, op2);
	if (cmp == 0)
	{
		bigint_set_ui(res, 0);
		return (1);
	}
	else if (cmp > 0)
	{
		res->sign = BIGINT_NEG;
		return (bigint_sub_abs(res, op1, op2));
	}
	else
	{
		res->sign = BIGINT_POS;
		return (bigint_sub_abs(res, op2, op1));
	}
}
