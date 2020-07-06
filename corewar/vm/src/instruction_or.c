/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:45:34 by jarcher           #+#    #+#             */
/*   Updated: 2020/06/27 01:52:21 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** set_carry() - Set instruction carry
** @process: The current process
*/

static void	set_carry(t_process *process)
{
	if (process->registers[process->current_instruction.args[2] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
}

/*
** ins_or() - or instruction
** @arena: The arena
** @process: The current process
**
** Does a binary OR between two direct, indirect or register values
** (first and second arg) and stores the result in a register (third arg)
** Modifies the carry
**
** Return: 0
*/

int			ins_or(t_arena *arena, t_process *process)
{
	int32_t	value1;
	int32_t	value2;

	if (process->current_instruction.args_type[0] == IND_ARG)
		value1 = (int32_t)get_value_in_memory(arena, process,
		((int16_t)process->current_instruction.args[0] % IDX_MOD));
	else if (process->current_instruction.args_type[0] == REG_ARG)
		value1 = (int32_t)process->
			registers[process->current_instruction.args[0] - 1];
	else
		value1 = (int32_t)process->current_instruction.args[0];
	if (process->current_instruction.args_type[1] == IND_ARG)
		value2 = (int32_t)get_value_in_memory(arena, process,
		((int16_t)process->current_instruction.args[1] % IDX_MOD));
	else if (process->current_instruction.args_type[1] == REG_ARG)
		value2 = (int32_t)process->
			registers[process->current_instruction.args[1] - 1];
	else
		value2 = (int32_t)process->current_instruction.args[1];
	process->registers[process->current_instruction.args[2] - 1] =
		value1 | value2;
	set_carry(process);
	return (EXIT_SUCCESS);
}
