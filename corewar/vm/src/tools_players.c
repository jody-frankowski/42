/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:10:41 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/26 22:41:18 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** init_players() - init players in @arena
**
** Initialize all @arena->player
*/

void			init_players(t_arena *arena)
{
	int			index;

	index = 0;
	while (index < MAX_PLAYERS)
	{
		arena->players[index].filename = NULL;
		bzero(arena->players[index].name, PROG_NAME_LENGTH + 1);
		bzero(arena->players[index].comment, PROG_COMMENT_LENGTH + 1);
		arena->players[index].header_size = 0;
		arena->players[index].number = 0;
		arena->players[index].is_alive = 1;
		arena->players[index].last_live = 0;
		index++;
	}
}

/*
** player_alive() - return number of players still alive in @arena
**
** Browse players in arena and count how much are still alive
** Return: number of player(s) still alive
*/

int				player_alive(t_arena *arena)
{
	int			i;
	int			alive;
	int			ret;

	i = 0;
	ret = 0;
	while (i++ < MAX_PLAYERS)
	{
		if (arena->players[i - 1].number != 0)
		{
			alive = arena->players[i - 1].is_alive;
			if (alive == 1)
				ret++;
		}
	}
	return (ret);
}

/*
** nb_process_player() - total player alive processes
** @player_ind: index of concerned player
**
** Return: Total of still alive processes for concerned player
*/

int				nb_process_player(t_arena *arena, int player_ind)
{
	int			ret;
	t_process	*browse;

	ret = 0;
	browse = arena->processes;
	while (browse)
	{
		if (browse->player == player_ind)
			ret++;
		if (browse->next != NULL)
			browse = browse->next;
		else
			browse = NULL;
	}
	return (ret);
}
