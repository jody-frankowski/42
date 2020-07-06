/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarcher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:45:39 by jarcher           #+#    #+#             */
/*   Updated: 2020/03/10 14:45:41 by jarcher          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ins_st() - st instruction
** @arena: The arena
** @process: The current process
**
** Stores the value of a register (first arg) in memory @ PC + VAL % IDX_MOD
** or in a register VAL where VAL is an indirect or register value (second arg)
**
** Return: 0
*/

int		ins_st(t_arena *arena, t_process *process)
{
	if (process->current_instruction.args_type[1] == REG_ARG)
		process->registers[process->current_instruction.args[1] - 1] =
			process->registers[process->current_instruction.args[0] - 1];
	else
		write_in_memory(arena, process,
			(int16_t)process->current_instruction.args[1] % IDX_MOD,
			process->registers[process->current_instruction.args[0] - 1]);
	return (EXIT_SUCCESS);
}
