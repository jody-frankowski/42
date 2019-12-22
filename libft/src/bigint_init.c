/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bigint_init.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/05 23:23:55 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/05 23:23:55 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "bigint.h"
#include "libft.h"

/*
** bigint_init() - Initialize @num and set it to 0
** @num: The bigint variable to set.
**
** Return: 1 on success, 0 on error.
*/

int		bigint_init(t_bigint num)
{
	num->sign = BIGINT_POS;
	if (!(num->val = malloc(1 * sizeof(*num->val))))
		return (0);
	num->val[0] = 0;
	num->size = 1;
	return (1);
}

/*
** bigint_free() - Free a bigint
** @num: The bigint to free.
*/

void	bigint_free(t_bigint num)
{
	free(num->val);
}

/*
** bigint_fix_size() - Fix the size of a bigint
** @num: The bigint to fix
**
** This will "fix", more specifically reduce the size of the bigint to the
** smallest size possible. This is currently used by bigint_sub_abs().
*/

void	bigint_fix_size(t_bigint num)
{
	int i;

	i = num->size - 1;
	while (i >= 0)
	{
		if (num->val[i] != 0)
		{
			num->size = i + 1;
			return ;
		}
		i--;
	}
	num->size = 1;
}

/*
** bigint_alloc_one_more() - Allocate one more element in num->val array
** @num: The bigint to modify
**
** Return: 1 on success. 0 on error.
*/

int		bigint_alloc_one_more(t_bigint num)
{
	if (!(num->val = ft_realloc(
			num->val,
			sizeof(*num->val) * (num->size),
			sizeof(*num->val) * (num->size + 1))))
		return (0);
	ft_memset(num->val + num->size, 0, sizeof(*num->val) * 1);
	num->size += 1;
	return (1);
}
