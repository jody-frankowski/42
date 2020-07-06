/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:10:48 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/27 19:11:13 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** print_winner() - Print the winner
**
** Print the last player still alive
*/

void	print_winner(t_arena *arena)
{
	int	i;
	int	winner;

	i = 0;
	winner = 0;
	if (process_alive(arena) != 0)
		free_and_exit(arena);
	while (i < MAX_PLAYERS)
	{
		if (arena->players[winner].filename == NULL ||
			arena->players[i].last_live > arena->players[winner].last_live)
			winner = i;
		i++;
	}
	ft_printf("Le joueur %d (%s) a gagne\n",
	ft_absolute(arena->players[winner].number), arena->players[winner].name);
	free_and_exit(arena);
}

/*
** dump_memory() - Dump the memory and exit()
**
** Dump the memory by and exit programm
*/

void	dump_memory(t_arena *arena)
{
	int	i;

	i = 0;
	if (arena->visu == 1)
	{
		curs_set(1);
		endwin();
	}
	while (i < MEM_SIZE)
	{
		if (i % 32 == 0 || i == 0)
			ft_printf("0x%04x : ", i);
		ft_printf("%.2hhx", arena->memory[i].value);
		if ((i + 1) % 32 == 0)
			ft_printf("\n");
		else if ((i + 1) % 8 == 0)
			ft_printf("  ");
		else
			ft_printf(" ");
		i++;
	}
}

/*
** free_and_exit() - Call last_free and exit
*/

void	free_and_exit(t_arena *arena)
{
	if (arena->visu == 1)
	{
		curs_set(1);
		endwin();
	}
	last_free(arena);
	exit(EXIT_SUCCESS);
}
