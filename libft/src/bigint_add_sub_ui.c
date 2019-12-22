/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bigint_add_sub_ui.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/06 01:29:04 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/06 01:29:04 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "bigint.h"

/*
** bigint_add_ui - Add an unsigned int to a bigint
** @res: The result of the addition
** @op1: The bigint to add to
** @op2: The unsigned int to add
**
** Return: 1 on success. 0 on error.
*/

int	bigint_add_ui(t_bigint res, t_bigint op1, unsigned long op2)
{
	t_bigint	op2_bigint;
	int			error;

	bigint_init(op2_bigint);
	bigint_set_ui(op2_bigint, op2);
	error = bigint_add(res, op1, op2_bigint);
	bigint_free(op2_bigint);
	return (error);
}

/*
** bigint_sub_ui - Subtract an unsigned int from a bigint
** @res: The result of the subtraction
** @op1: The bigint to subtract from
** @op2: The unsigned int to subtract to
**
** Return: 1 on success. 0 on error.
*/

int	bigint_sub_ui(t_bigint res, t_bigint op1, unsigned long op2)
{
	t_bigint	op2_bigint;
	int			error;

	bigint_init(op2_bigint);
	bigint_set_ui(op2_bigint, op2);
	error = bigint_sub(res, op1, op2_bigint);
	bigint_free(op2_bigint);
	return (error);
}
