/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_equal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

/*
** ins_equal() - Check if two instructions are equal
** @a: The first instruction to compare
** @b: The second instruction to compare
**
** /!\ Extras fields in args and args_typeo aren't checked.
**
** Return: If equal true, else false.
*/

bool	ins_equal(t_ins *a, t_ins *b)
{
	size_t i;

	if (a->instruction != b->instruction)
		return (false);
	if (a->instruction == NULL)
		return (true);
	if (a->size != b->size)
		return (false);
	i = 0;
	while (i < a->instruction->num_args)
	{
		if (a->args_type[i] != b->args_type[i] ||
			a->args[i] != b->args[i])
			return (false);
		i++;
	}
	return (true);
}
