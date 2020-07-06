/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarcher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:45:22 by jarcher           #+#    #+#             */
/*   Updated: 2020/03/10 14:45:24 by jarcher          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ins_lld() - lld instruction
** @arena: The arena
** @process: The current process
**
** Loads a direct or indirect value (first arg) into a register (second arg)
** Without %IDX_MOD
** Modifies the carry
**
** Return: 0
*/

int		ins_lld(t_arena *arena, t_process *process)
{
	if (process->current_instruction.args_type[0] == IND_ARG)
		process->registers[process->current_instruction.args[1] - 1] =
			get_value_in_memory(arena, process,
			(int16_t)process->current_instruction.args[0]);
	else if (process->current_instruction.args_type[0] == DIR_ARG)
		process->registers[process->current_instruction.args[1] - 1] =
		process->current_instruction.args[0];
	if (process->registers[process->current_instruction.args[1] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (EXIT_SUCCESS);
}
