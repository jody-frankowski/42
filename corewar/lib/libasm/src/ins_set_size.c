/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_set_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

/*
** ins_set_size() - Set the size of an ins
** @ins: A pointer to the ins to modify
*/

void	ins_set_size(t_ins *ins)
{
	size_t	i;

	ins->size = 0;
	if (!ins->instruction)
		return ;
	ins->size = 1;
	if (ins->instruction->has_acb)
		ins->size++;
	i = 0;
	while (i < ins->instruction->num_args)
	{
		if (ins->args_type[i] == REG_ARG)
			ins->size += REG_ARG_SIZE;
		else if (ins->args_type[i] == DIR_ARG)
			ins->size += ins->instruction->direct_arg_size;
		else
			ins->size += IND_ARG_SIZE;
		i++;
	}
}
