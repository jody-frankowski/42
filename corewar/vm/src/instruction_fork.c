/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarcher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:45:02 by jarcher           #+#    #+#             */
/*   Updated: 2020/03/10 14:45:04 by jarcher          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ins_fork() - fork instruction
** @arena: The arena
** @process: The current process
**
** Creates a new child process that will inherit
** the register values of its parent
** and whose PC will be PC + VAL % IDX_MOD
** where VAL is a direct value (first arg)
**
** Return: 0
*/

int		ins_fork(t_arena *arena, t_process *process)
{
	t_process	*new;
	int16_t		value;

	(void)arena;
	new = NULL;
	if (add_process(arena, &process, &new, process->player) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	copy_registers(process, new);
	new->carry = process->carry;
	new->last_live = process->last_live;
	value = process->pc +
		((int16_t)process->current_instruction.args[0] % IDX_MOD);
	while (value < 0)
		value += MEM_SIZE;
	new->pc = value % MEM_SIZE;
	return (EXIT_SUCCESS);
}
