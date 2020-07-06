/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarcher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:45:43 by jarcher           #+#    #+#             */
/*   Updated: 2020/03/10 14:45:44 by jarcher          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ins_sti() - sti instruction
** @arena: The arena
** @process: The current process
**
** Stores the value of a register (first arg) in memory
** @ PC + (VAL1 + VAL2) % IDX_MOD
** where VAL1 is a direct, indirect or register value (second arg)
** and VAL2 is a direct or register value (third arg)
**
** Return: 0
*/

int		ins_sti(t_arena *arena, t_process *process)
{
	int32_t	value;

	if (process->current_instruction.args_type[1] == IND_ARG)
		value = (int32_t)get_value_in_memory(arena, process,
		((int16_t)process->current_instruction.args[1] % IDX_MOD));
	else if (process->current_instruction.args_type[1] == REG_ARG)
		value = (int32_t)process->
			registers[process->current_instruction.args[1] - 1];
	else
		value = (int16_t)process->current_instruction.args[1];
	value += process->current_instruction.args_type[2] == REG_ARG ?
		(int32_t)process->registers[process->current_instruction.args[2] - 1] :
		(int16_t)process->current_instruction.args[2];
	write_in_memory(arena, process, (value % IDX_MOD),
		process->registers[process->current_instruction.args[0] - 1]);
	return (EXIT_SUCCESS);
}
