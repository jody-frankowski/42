/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visulizer_hud.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:31:10 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/27 18:58:49 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** get_player_color() - return color pair corresponding to @player
** @player: index of concerned player
*/

int		get_player_color(t_arena *arena, int player)
{
	int pair;

	pair = 0;
	if (arena->players[player].number == -1)
		pair = 1;
	else if (arena->players[player].number == -2)
		pair = 2;
	else if (arena->players[player].number == -3)
		pair = 3;
	else if (arena->players[player].number == -4)
		pair = 4;
	return (pair);
}

/*
** draw_players_info() - draw players info in HUD
*/

void	draw_players_info(t_arena *arena)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (arena->players[i].number != 0)
		{
			wattron(arena->window, COLOR_PAIR(get_player_color(arena, i)));
			if (ft_strlen(arena->players[i].name) >= 25)
				mvwprintw(arena->window, 4 + i, 200,
				"Player %d : %.22s... | %-9d | %3d", i + 1,
				arena->players[i].name, arena->players[i].last_live,
				nb_process_player(arena, i));
			else
				mvwprintw(arena->window, 4 + i, 200,
				"Player %d : %-22s    | %-9d | %3d", i + 1,
				arena->players[i].name, arena->players[i].last_live,
				nb_process_player(arena, i));
		}
		i++;
	}
}

/*
** draw_hud() - draw the HUD
**
** Drawing line seperator, player real-time informations
** and some information about the arena
*/

void	draw_hud(t_arena *arena)
{
	wattron(arena->window, COLOR_PAIR(10));
	mvwprintw(arena->window, 2, 211,
		"Name                      | Last live | Processes");
	mvhline(10, 206, 0, 41);
	mvwprintw(arena->window, 12, 215, "CURRENT CYCLE : %d", arena->cycle);
	mvwprintw(arena->window, 14, 200, "Next check     : %d",
		arena->next_check);
	mvwprintw(arena->window, 15, 200, "Cycle interval : %d",
		arena->cycle_to_die);
	mvwprintw(arena->window, 16, 200, "Total live     : %d", arena->nb_lives);
	mvwprintw(arena->window, 17, 200, "Nb processes   : %d", arena->nb_process);
	mvhline(19, 206, 0, 41);
	mvwprintw(arena->window, 21, 200, "Speed up       : +");
	mvwprintw(arena->window, 22, 200, "Speed down     : -");
	draw_players_info(arena);
	wattroff(arena->window, COLOR_PAIR(1));
}
