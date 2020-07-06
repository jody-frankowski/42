/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarcher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:44:15 by jarcher           #+#    #+#             */
/*   Updated: 2020/03/10 14:44:21 by jarcher          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ins_add() - add instruction
** @arena: The arena
** @process: The current process
**
** Adds a register (first arg) to another (second arg)
** and stores the result in a register (third arg)
** Modifies the carry
**
** Return: 0
*/

int		ins_add(t_arena *arena, t_process *process)
{
	(void)arena;
	process->registers[process->current_instruction.args[2] - 1] =
		process->registers[process->current_instruction.args[0] - 1] +
		process->registers[process->current_instruction.args[1] - 1];
	if (process->registers[process->current_instruction.args[2] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (EXIT_SUCCESS);
}
