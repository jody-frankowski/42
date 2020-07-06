/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarcher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:45:45 by jarcher           #+#    #+#             */
/*   Updated: 2020/03/10 14:45:47 by jarcher          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ins_sub() - sub instruction
** @arena: The arena
** @process: The current process
**
** Subtracts a register (first arg) from another (second arg)
** and stores the result in a register (third arg)
** Modifies the carry
**
** Return: 0
*/

int		ins_sub(t_arena *arena, t_process *process)
{
	(void)arena;
	process->registers[process->current_instruction.args[2] - 1] =
		process->registers[process->current_instruction.args[0] - 1] -
		process->registers[process->current_instruction.args[1] - 1];
	if (process->registers[process->current_instruction.args[2] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (EXIT_SUCCESS);
}
