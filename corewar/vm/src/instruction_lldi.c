/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarcher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:45:31 by jarcher           #+#    #+#             */
/*   Updated: 2020/03/10 14:45:32 by jarcher          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ins_lldi() - lldi instruction
** @arena: The arena
** @process: The current process
**
** Loads a value from memory @ PC + (VAL1 + VAL2)
** where VAL1 is a direct, indirect or register value (first arg)
** and VAL2 is a direct or register value (second arg),
** into a register (third value)
** Modifies the carry
**
** Return: 0
*/

int		ins_lldi(t_arena *arena, t_process *process)
{
	int32_t	value;

	if (process->current_instruction.args_type[0] == IND_ARG)
		value = (int32_t)get_value_in_memory(arena, process,
			(int16_t)process->current_instruction.args[0]);
	else if (process->current_instruction.args_type[0] == REG_ARG)
		value = (int32_t)process->
			registers[process->current_instruction.args[0] - 1];
	else
		value = (int16_t)process->current_instruction.args[0];
	value += process->current_instruction.args_type[1] == REG_ARG ?
		(int32_t)process->registers[process->current_instruction.args[1] - 1] :
		(int16_t)process->current_instruction.args[1];
	process->registers[process->current_instruction.args[2] - 1] =
		get_value_in_memory(arena, process, value);
	if (process->registers[process->current_instruction.args[2] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (EXIT_SUCCESS);
}
