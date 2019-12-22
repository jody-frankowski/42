/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bigint_mul.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/05 23:23:55 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/05 23:23:55 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "bigint.h"

/*
** This is a helper function extracted from bigint_mul because of The Norm.
** It sets @count to the lower absolute number between @op1 and @op2 in order to
** make as few additions as possible.
*/

int	bigint_set_count_and_num(
	t_bigint op1,
	t_bigint op2,
	t_bigint count,
	t_bigint num
)
{
	if (!bigint_init(count))
		return (0);
	if (!bigint_init(num) && bigint_free(count))
		return (0);
	if (bigint_cmpabs(op1, op2) > 0)
	{
		if (!bigint_set(num, op1) && bigint_free(count) && bigint_free(num))
			return (0);
		if (!bigint_abs(count, op2) && bigint_free(count) && bigint_free(num))
			return (0);
	}
	else
	{
		if (!bigint_set(num, op2) && bigint_free(count) && bigint_free(num))
			return (0);
		if (!bigint_abs(count, op1) && bigint_free(count) && bigint_free(num))
			return (0);
	}
	return (1);
}

/*
** bigint_mul() - Multiply two bigint together
** @res: The result of the multiplication
** @op1: The first bigint to multiply
** @op2: The second bigint to multiply with
**
** @res can point to the same bigint as @op1 or @op2 or both.
**
** Return: 1 on success. 0 on error.
*/

int	bigint_mul(t_bigint res, t_bigint op1, t_bigint op2)
{
	t_bigint count;
	t_bigint num;
	t_bigint res_tmp;

	if (!bigint_init(res_tmp))
		return (0);
	if (!bigint_set_count_and_num(op1, op2, count, num) && bigint_free(res_tmp))
		return (0);
	while (bigint_cmp_si(count, 0) != 0)
	{
		bigint_add(res_tmp, res_tmp, num);
		bigint_sub_ui(count, count, 1);
	}
	if ((op1->sign == BIGINT_POS && op2->sign == BIGINT_POS) || \
		(op1->sign == BIGINT_NEG && op2->sign == BIGINT_NEG))
		res_tmp->sign = BIGINT_POS;
	else
		res_tmp->sign = BIGINT_NEG;
	if (!(bigint_set(res, res_tmp)))
		return (0);
	bigint_free(count);
	bigint_free(num);
	bigint_free(res_tmp);
	return (1);
}
