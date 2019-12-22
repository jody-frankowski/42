/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bigint_set.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/06 01:29:04 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/06 01:29:04 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "bigint.h"
#include "libft.h"

/*
** bigint_set() - Set a bigint from another one
** @res: The bigint to set
** @num: The bigint to copy from
**
** Return: 1 on success. 0 on error.
*/

int		bigint_set(t_bigint res, t_bigint num)
{
	res->sign = num->sign;
	res->size = num->size;
	free(res->val);
	if (!(res->val = malloc(num->size * sizeof(*num->val))))
		return (0);
	ft_memmove(res->val, num->val, num->size * sizeof(*num->val));
	return (1);
}

/*
** bigint_set_si() - Set a bigint from a signed integer
** @res: The bigint to set
** @si:  The signed integer value to use
*/

void	bigint_set_si(t_bigint res, signed long si)
{
	res->val[0] = si < 0 ? -(unsigned long)si : (unsigned long)si;
	res->sign = si >= 0 ? BIGINT_POS : BIGINT_NEG;
	res->size = 1;
}

/*
** bigint_set_ui() - Set a bigint from an unsigned integer
** @res: The bigint to set
** @ui:  The unsigned integer value to use
*/

void	bigint_set_ui(t_bigint res, unsigned long ui)
{
	res->val[0] = ui;
	res->sign = BIGINT_POS;
	res->size = 1;
}
