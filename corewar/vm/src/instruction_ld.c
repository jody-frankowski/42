/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_ld.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:45:06 by jarcher           #+#    #+#             */
/*   Updated: 2020/06/27 01:44:54 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ins_ld() - ld instruction
** @arena: The arena
** @process: The current process
**
** Loads a direct or indirect value (first arg) into a register (second arg)
** Modifies the carry
**
** Return: 0
*/

int		ins_ld(t_arena *arena, t_process *process)
{
	if (process->current_instruction.args_type[0] == IND_ARG)
		process->registers[process->current_instruction.args[1] - 1] =
			get_value_in_memory(arena, process,
			((int16_t)process->current_instruction.args[0] % IDX_MOD));
	else if (process->current_instruction.args_type[0] == DIR_ARG)
		process->registers[process->current_instruction.args[1] - 1] =
		process->current_instruction.args[0];
	if (process->registers[process->current_instruction.args[1] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (EXIT_SUCCESS);
}
