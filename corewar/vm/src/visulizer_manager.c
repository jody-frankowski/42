/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visulizer_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:10:37 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/26 22:25:03 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** init_screnn() - initialise the window
**
** Init color pairs, init the window and draw box
*/

void	init_screen(t_arena *arena)
{
	initscr();
	noecho();
	start_color();
	use_default_colors();
	curs_set(0);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_WHITE, COLOR_GREEN);
	init_pair(6, COLOR_WHITE, COLOR_CYAN);
	init_pair(7, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(8, COLOR_WHITE, COLOR_YELLOW);
	init_pair(10, COLOR_WHITE, COLOR_BLACK);
	arena->window = subwin(stdscr, 66, 280, 0, 0);
	box(arena->window, ACS_VLINE, ACS_HLINE);
	draw_arena(arena);
	wrefresh(arena->window);
	refresh();
}

/*
** get_event() - keyboard event management
*/

void	get_event(t_arena *arena)
{
	int c;

	nodelay(arena->window, true);
	c = wgetch(arena->window);
	if (c == 43)
		arena->speed /= 2;
	else if (c == 45)
		arena->speed *= 2;
	else if (c == 27)
		free_and_exit(arena);
	else if (c == 32)
	{
		c = 0;
		while (c != 32)
		{
			c = wgetch(arena->window);
			if (c == 27)
				free_and_exit(arena);
		}
	}
	if (arena->speed > 100000)
		arena->speed = 100000;
	if (arena->speed <= 0)
		arena->speed = 0.01;
}
