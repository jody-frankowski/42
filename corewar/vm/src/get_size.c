/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarcher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 08:45:22 by jarcher           #+#    #+#             */
/*   Updated: 2020/06/27 09:45:24 by jarcher          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** set_size() - Set the size of an ins
** @ins: A pointer to the ins to modify
**
** Set size of an instruction with acb
*/

static void	set_size(t_ins *ins)
{
	size_t	i;

	ins->size = 2;
	i = 0;
	while (i < ins->instruction->num_args)
	{
		if (ins->args_type[i] == REG_ARG)
			ins->size += REG_ARG_SIZE;
		else if (ins->args_type[i] == DIR_ARG)
			ins->size += ins->instruction->direct_arg_size == 0 ?
				4 : ins->instruction->direct_arg_size;
		else if (ins->args_type[i] == IND_ARG)
			ins->size += IND_ARG_SIZE;
		else
			ins->size += 0;
		i++;
	}
}

/*
** get_ins_size() - Set size of instruction with acb
** @ins: A pointer to the ins to modify
** @bin: Buffer with the acb
**
** Set size of an instruction with acb
*/

void		get_ins_size(t_ins *ins, char *bin)
{
	if (ins->instruction == NULL || !ins->instruction->has_acb)
		ins->size = 1;
	else
	{
		ins_set_args_type(ins, &bin);
		set_size(ins);
	}
}
