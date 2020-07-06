/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
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
**
** Return: 1 as a convenience for The Norm.
*/

int		bigint_free(t_bigint num)
{
	free(num->val);
	return (1);
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

/*
** bigint_realloc() - Reallocate a bigint
** @num: The bigint to reallocate
** @new_size: The new size
**
** TODO Broken: Invalid write of size 1
**
** Return: 1 on success. 0 on error.
*/

int		bigint_realloc(t_bigint num, size_t new_size)
{
	if (!(num->val = ft_realloc(
			num->val,
			sizeof(*num->val) * num->size,
			sizeof(*num->val) * new_size)))
		return (0);
	ft_memset(num->val + (sizeof(*num->val) * num->size),
				0,
				sizeof(*num->val) * (new_size - num->size));
	num->size = new_size;
	return (1);
}
