/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:10:45 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/26 22:42:45 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** del_all_process() - del all processes in @process
** @process: Processes chained list
**
** Del all processes from @process chained list
*/

void			del_all_processes(t_process **process)
{
	t_process	*prev;
	t_process	*tmp;

	tmp = *process;
	while (tmp)
	{
		prev = tmp;
		tmp = tmp->next;
		del_process(&prev);
	}
	*process = NULL;
}

/*
** free_players() - free all players in @arena
**
** Browse all players and delete & free all processes for each of them
*/

void			free_players(t_arena *arena)
{
	int			i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (arena->players[i].filename != NULL)
		{
			free(arena->players[i].filename);
			arena->players[i].filename = NULL;
		}
		i++;
	}
}

/*
** last_free() - free @arena
**
** Free players and @arena
*/

void			last_free(t_arena *arena)
{
	del_all_processes(&(arena->processes));
	free_players(arena);
	free(arena);
}
