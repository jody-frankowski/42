/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 13:21:37 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/27 13:51:35 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** write_in_memory() - Writes a value in memory
** @arena:   The arena
** @process: The current process
** @index:   The position
** @nb	:    The value to write
**
** Writes nb at current_position + index
*/

void			write_in_memory(t_arena *arena, t_process *process,
				int index, uint32_t nb)
{
	uint32_t	val;
	int			i;

	index += process->pc;
	if (index > 0)
		index = index % MEM_SIZE;
	while (index < 0)
		index += MEM_SIZE;
	val = ft_htobe32(nb);
	i = 0;
	while (i < 4)
	{
		arena->memory[index].value = val & 0xff;
		val = val >> 8;
		arena->memory[index].player = &(arena->players[process->player]);
		if (++index == MEM_SIZE)
			index = 0;
		++i;
	}
}

/*
** get_value_in_memory() - Get a value from memory
** @arena:   The arena
** @process: The current process
** @index:   The position
**
** Gets nb at current_position + index
**
** Return: the value at current_position + index
*/

uint32_t		get_value_in_memory(t_arena *arena,
						t_process *process, int index)
{
	char		bytes[4];
	uint32_t	*val;
	int			i;

	index += process->pc;
	if (index > 0)
		index = index % MEM_SIZE;
	while (index < 0)
		index += MEM_SIZE;
	i = 0;
	while (i < 4)
	{
		bytes[i] = (unsigned char)arena->memory[index].value;
		if (++index == MEM_SIZE)
			index = 0;
		++i;
	}
	val = (uint32_t *)&bytes[0];
	return (ft_betoh32(*val));
}
