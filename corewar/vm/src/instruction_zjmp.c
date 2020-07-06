/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarcher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:45:51 by jarcher           #+#    #+#             */
/*   Updated: 2020/03/10 14:45:51 by jarcher          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ins_zjmp() - zjmp instruction
** @arena: The arena
** @process: The current process
**
** If the carry is 1,
** jumps to an address specified as a direct value (first arg)
**
** Return: 0
*/

int		ins_zjmp(t_arena *arena, t_process *process)
{
	int16_t		value;

	(void)arena;
	if (process->carry == 1)
	{
		value = process->pc +
			(int16_t)process->current_instruction.args[0] % IDX_MOD;
		while (value < 0)
			value += MEM_SIZE;
		process->pc = value % MEM_SIZE;
	}
	else
		process->pc = (process->pc + 3) % MEM_SIZE;
	return (EXIT_SUCCESS);
}
