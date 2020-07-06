/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_live.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:45:19 by jarcher           #+#    #+#             */
/*   Updated: 2020/06/27 01:46:34 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ins_live() - live instruction
** @arena: The arena
** @process: The current process
**
** Notifies the VM that the process is alive,
** and with a direct value (first arg)
** that the player whose number is the same is alive
**
** Return: 0
*/

int		ins_live(t_arena *arena, t_process *process)
{
	uint	i;

	i = 0;
	while (i < MAX_PLAYERS && (arena->players[i].filename == NULL ||
		arena->players[i].number !=
		(int32_t)process->current_instruction.args[0]))
		++i;
	if (i < MAX_PLAYERS)
	{
		arena->players[i].last_live = arena->cycle;
		if (arena->aff == 1 && arena->visu == 0)
		{
			ft_printf("Player %s (%d) has been reported as alive ",
				arena->players[i].name, arena->players[i].number);
			ft_printf("at cycle %d by process %d\n",
				arena->cycle, process->process_number);
		}
	}
	process->last_live = arena->cycle;
	arena->nb_lives += 1;
	return (EXIT_SUCCESS);
}
