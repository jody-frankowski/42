/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:10:40 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/26 22:40:10 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** copy_registers() - copy @src registers to @dest resgisers
** @src:  process src
** @dest: process destination
**
** copy resgisters from @src process to @dest process
*/

void			copy_registers(t_process *src, t_process *dest)
{
	int			i;

	i = 0;
	while (i < REGISTERS_COUNT)
	{
		dest->registers[i] = src->registers[i];
		i++;
	}
}

/*
** init_process() - Init @process
** @process:     process to init
** @prev:        last process from the chained list
** @player_ind:  Index of player concerned by the process
**
** Init @process and link it to @prev process
*/

void			init_process(t_arena *arena, t_process *process,
	t_process **prev, int player_ind)
{
	ft_bzero(process->registers, REGISTERS_COUNT * sizeof(unsigned int));
	process->registers[0] = -(player_ind + 1);
	init_instruction(process);
	++arena->nb_process;
	process->process_number = arena->nb_process;
	process->instruction_end = 0;
	process->last_live = 0;
	process->pc = 0;
	process->carry = 0;
	process->player = player_ind;
	process->prev = NULL;
	process->next = NULL;
	if (prev != NULL)
		process->prev = *prev;
	else
		process->next = NULL;
}

/*
** add_process() - add a process in chained list
** @processes:   processes chained list
** @new:         process to add
** @player_ind:  Index of player concerned by the process
**
** add @new at the end of @processes chained list
*/

int				add_process(t_arena *arena, t_process **processes,
	t_process **new, int player_ind)
{
	t_process	*tmp;

	tmp = *processes;
	if (!((*new) = malloc(sizeof(t_process))))
		return (EXIT_FAILURE);
	if (*processes == NULL)
	{
		init_process(arena, *new, NULL, player_ind);
		*processes = *new;
		arena->last_process = *new;
		return (EXIT_SUCCESS);
	}
	tmp = arena->last_process;
	tmp->next = *new;
	init_process(arena, *new, &tmp, player_ind);
	arena->last_process = *new;
	return (EXIT_SUCCESS);
}

/*
** del_process() - del a process
** @process: process to del
**
** del and free @process, and link prev and next process in the chained list
*/

void			del_process(t_process **process)
{
	t_process	*tmp;

	tmp = *process;
	if (tmp->prev != NULL)
		tmp->prev->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = tmp->prev;
	free(tmp);
	*process = NULL;
}

/*
** process_alive() - total alive processes
**
** Return: Total of still alive processes
*/

int				process_alive(t_arena *arena)
{
	int			ret;
	t_process	*tmp;

	ret = 0;
	tmp = arena->processes;
	while (tmp)
	{
		ret++;
		if (tmp->next != NULL)
			tmp = tmp->next;
		else
			tmp = NULL;
	}
	return (ret);
}
