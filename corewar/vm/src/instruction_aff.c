/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarcher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:44:53 by jarcher           #+#    #+#             */
/*   Updated: 2020/03/10 14:44:55 by jarcher          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ins_aff() - aff instruction
** @arena: The arena
** @process: The current process
**
** Prints a register value (first arg) modulo 256
** interpreted as an ASCII character on the standard output
**
** Return: 0
*/

int		ins_aff(t_arena *arena, t_process *process)
{
	(void)arena;
	if (arena->aff == 1 && arena->visu == 0)
	{
		ft_printf("Aff: %c\n", process->registers[process->
			current_instruction.args[0] - 1] % 256);
	}
	return (EXIT_SUCCESS);
}
