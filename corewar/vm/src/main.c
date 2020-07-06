/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:09:58 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/27 18:20:18 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		print_player(t_arena *arena)
{
	int		index;

	index = 0;
	ft_printf("Introducing players...\n");
	while (index < MAX_PLAYERS)
	{
		if (arena->players[index].filename != NULL)
		{
			ft_printf(
			"player[%d] %2d, filename = %s, name : %s, comment : %s\n",
			index, ft_absolute(arena->players[index].number),
			arena->players[index].filename, arena->players[index].name,
			arena->players[index].comment);
		}
		index++;
	}
}

int			main(int ac, char **av)
{
	t_arena	*arena;

	arena = NULL;
	if (!(arena = malloc(sizeof(t_arena))))
		return (EXIT_FAILURE);
	if (init_arena(arena) == EXIT_FAILURE)
	{
		free(arena);
		return (EXIT_FAILURE);
	}
	read_params(ac, av, arena);
	print_player(arena);
	cycle(arena);
	last_free(arena);
	return (EXIT_SUCCESS);
}
