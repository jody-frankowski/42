/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visulizer_drawing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:10:38 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/26 22:36:34 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** draw_pc() - draw program pc
**
** Highlight position of programs pc
*/

void			draw_pc(t_arena *arena)
{
	int			pc;
	t_process	*tmp;

	pc = 0;
	tmp = arena->processes;
	while (tmp)
	{
		pc = tmp->pc;
		wattron(arena->window, COLOR_PAIR(tmp->player + 5));
		mvwprintw(arena->window, 1 + (pc / 64), 3 + (pc % 64) * 3,
			"%.2hhX", arena->memory[pc].value);
		tmp = tmp->next;
	}
}

/*
** refill_map() - print memory(@mem_case)
** @line_index: vertical position
** @col_index:  horizontal position
** @mem_case:   number of memory case
*/

void			refill_map(t_arena *arena, int line_index,
	int col_index, int mem_case)
{
	if (arena->memory[mem_case].player != NULL)
		wattron(arena->window,
			COLOR_PAIR(ft_absolute(arena->memory[mem_case].player->number)));
	else
		wattron(arena->window, COLOR_PAIR(10));
	mvwprintw(arena->window, 2 + line_index, 3 + col_index * 3,
		"%.2hhX", arena->memory[mem_case].value);
	draw_pc(arena);
}

/*
** draw_arena() - drawing all the map stuffs
*/

void			draw_arena(t_arena *arena)
{
	int			mem_case;
	int			col_index;
	int			line_index;

	mem_case = 0;
	col_index = 0;
	line_index = -1;
	draw_hud(arena);
	while (mem_case < MEM_SIZE)
	{
		refill_map(arena, line_index, col_index, mem_case);
		col_index++;
		if (col_index == 64)
		{
			col_index = 0;
			line_index++;
		}
		mem_case++;
	}
	wrefresh(arena->window);
	refresh();
	usleep(arena->speed * 2);
}
