/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_div.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.h"

/*
** bigint_div() - Divide a bigint by another
** @q:   The result of the division
** @r:   The remainder of the division
** @op1: The bigint to divide
** @op2: The bigint to divide with
**
** @res can point to the same bigint as @op1 or @op2 or both.
** TODO free() on add/sub/set error. Not done because of the The Norm.
** TODO FIXME
** Removed for now because of The Norm:
** if ((op1->sign == BIGINT_POS && op2->sign == BIGINT_POS) || \
** 	(op1->sign == BIGINT_NEG && op2->sign == BIGINT_NEG))
** 	q_tmp->sign = BIGINT_POS;
** else
** 	q_tmp->sign = BIGINT_NEG;
**
** Return: 1 on success. 0 on error.
*/

int	bigint_div(t_bigint q, t_bigint r, t_bigint op1, t_bigint op2)
{
	t_bigint	q_tmp;
	int			i;

	bigint_init(q_tmp);
	bigint_set_ui(q_tmp, 0);
	bigint_set_ui(r, 0);
	bigint_realloc(q_tmp, op1->size);
	i = bigint_num_bits(op1);
	while (i-- != -1)
	{
		bigint_shift_left(r, r);
		bigint_set_bit(r, 0, bigint_get_bit(op1, i));
		if (bigint_cmpabs(r, op2) >= 0)
		{
			bigint_sub(r, r, op2);
			bigint_set_bit(q_tmp, i, 1);
		}
	}
	bigint_fix_size(q_tmp);
	bigint_set(q, q_tmp);
	bigint_free(q_tmp);
	return (1);
}
