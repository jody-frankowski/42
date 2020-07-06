/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:10:34 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/27 19:34:21 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** check_players_last_live() - Check if players are alive
**
** Browse each player and check if they exec "live" in time
*/

void			check_players_last_live(t_arena *arena)
{
	int			index;

	index = 0;
	while (index < MAX_PLAYERS)
	{
		if (arena->players[index].number != 0)
		{
			if (arena->players[index].last_live <
				arena->cycle - arena->cycle_to_die)
				arena->players[index].is_alive = 0;
		}
		index++;
	}
}

/*
** check_processes() - check all process
**
** kills processes that did not exec "live" since last check
*/

void			check_processes(t_arena *arena)
{
	t_process	*tmp;
	t_process	*prev;

	tmp = arena->processes;
	if (arena->cycle_to_die > arena->cycle)
		return ;
	while (tmp)
	{
		prev = tmp;
		tmp = tmp->next;
		if (arena->cycle_to_die < 0 || prev->last_live <=
			(unsigned int)(arena->cycle - arena->cycle_to_die))
		{
			if (arena->processes == prev)
				arena->processes = prev->next;
			if (arena->last_process == prev)
				arena->last_process = prev->prev;
			del_process(&prev);
		}
	}
}

/*
** check_lives() - Browse player for checking process, update cycle variables
**
** browse all players and exec check_processes for each of them
** if arena->nbr_live >= NBR_LIVE or arena->check_cycles_to_die == MAX_CHECKS
**     decrement arena->cycle_to_die
**     set arena->check_cycles_to_die
** else increment arena->cycle_to_die
*/

void			check_lives(t_arena *arena)
{
	arena->check_cycles_to_die++;
	check_processes(arena);
	if (arena->nb_lives >= NBR_LIVE ||
		arena->check_cycles_to_die == MAX_CHECKS)
	{
		arena->cycle_to_die -= CYCLE_DELTA;
		arena->check_cycles_to_die = 0;
	}
	arena->nb_lives = 0;
}

/*
** cycle() - the main programm loop
**
** Fill memory case with champion's bytecode,
** During the main while, check lives of each processes and players,
** execute instructions and update PC and cycles
*/

void			cycle(t_arena *arena)
{
	arena->next_check = CYCLE_TO_DIE;
	fill_memory_cases(arena);
	if (arena->visu == 1)
		init_screen(arena);
	--arena->dump;
	while (process_alive(arena) >= 1 && arena->dump != 0)
	{
		if (arena->visu == 1)
			get_event(arena);
		execute_all_processes(arena);
		if (arena->cycle_to_die < 0 || arena->cycle == arena->next_check)
		{
			check_players_last_live(arena);
			check_lives(arena);
			arena->next_check = arena->cycle + arena->cycle_to_die;
		}
		if (arena->visu == 1)
			draw_arena(arena);
		if (arena->dump != -2)
			arena->dump--;
		arena->cycle++;
	}
	if (arena->dump != -2)
		dump_memory(arena);
	print_winner(arena);
}
