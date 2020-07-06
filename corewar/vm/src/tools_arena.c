/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_arena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:10:48 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/27 13:51:51 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** init_arena() - Init @arena
** @arena: arena to init
**
** Return: EXIT_SUCCESS
*/

int				init_arena(t_arena *arena)
{
	arena->nb_players = 0;
	init_players(arena);
	ft_bzero(arena->memory, ((MEM_SIZE) * sizeof(t_mem_cell)));
	arena->processes = NULL;
	arena->last_process = NULL;
	arena->cycle = 1;
	arena->cycle_to_die = CYCLE_TO_DIE;
	arena->next_check = 0;
	arena->dump = -1;
	arena->aff = 0;
	arena->nb_lives = 0;
	arena->check_cycles_to_die = 0;
	arena->visu = 0;
	arena->window = NULL;
	arena->speed = 500;
	arena->nb_process = 0;
	return (EXIT_SUCCESS);
}

/*
** init_pc() - initialize player's PC
**
** Distributes players in the arena by initializing their PC
*/

void			init_pc(t_arena *arena)
{
	int			index;
	int			count;
	t_process	*new;

	index = 0;
	count = 0;
	new = NULL;
	while (index < MAX_PLAYERS)
	{
		if (arena->players[index].number != 0)
		{
			if (add_process(arena, &(arena->processes), &new, index))
				error(ERR_MALLOC, arena, NULL);
			if (arena->processes->next)
				arena->processes = arena->processes->next;
			arena->processes->pc = (MEM_SIZE / arena->nb_players) * count;
			count++;
		}
		index++;
	}
	while (arena->processes->prev)
		arena->processes = arena->processes->prev;
}

int				write_player_in_memory(t_arena *arena, int fd,
	int pc, int index)
{
	char		buff[1];

	while (read(fd, buff, 1) > 0)
	{
		arena->memory[pc].value = buff[0];
		arena->memory[pc].player = &arena->players[index];
		pc++;
	}
	return (pc);
}

/*
** fill_memory_case() - fill vm memory
**
** Read all players file and write it in arena->memory->value
*/

void			fill_memory_cases(t_arena *arena)
{
	int			index;
	int			pc;
	char		tmp[sizeof(t_prog_header)];
	int			fd;

	index = 0;
	init_pc(arena);
	while (index < MAX_PLAYERS)
	{
		if (arena->players[index].number != 0)
		{
			fd = open(arena->players[index].filename, O_RDONLY);
			if (fd == -1)
				error(ERR_READING, arena, tmp);
			pc = arena->processes->pc;
			if (arena->processes->next)
				arena->processes = arena->processes->next;
			if (!(read(fd, tmp, sizeof(t_prog_header))))
				error(ERR_READING, arena, tmp);
			pc = write_player_in_memory(arena, fd, pc, index);
		}
		index++;
	}
	while (arena->processes->prev)
		arena->processes = arena->processes->prev;
}
