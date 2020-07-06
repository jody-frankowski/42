/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:10:50 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/27 18:35:52 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** check_dump() - dump checker
** @av:    Array of parameters
** @index: Index of param to check (av[index])
**
** If -dump parameter is detect, check the param after -dumpgit pull
**
** Return: index avancement
*/

void				check_dump(t_arena *arena, char **av, int index)
{
	int				i;
	int				dump;

	i = 0;
	while (av[index][i])
	{
		if (ft_isdigit(av[index][i]) == 0)
			error(ERR_PARAM, arena, av[index]);
		i++;
	}
	dump = ft_atoi(av[index]);
	if (dump <= 0)
		error(ERR_PARAM, arena, ft_itoa(dump));
	arena->dump = dump + 1;
}

/*
** check_player() - player checker
** @av:     Array of parameters
** @number: Param after -n (= -1 if not -n)
** @index:  Index of param to check (av[index])
**
** check all elements of a player
*/

void				check_player
	(t_arena *arena, char **av, int number, int index)
{
	int				player_ind;
	int				fd;
	t_prog_header	*prog_header;

	if (arena->nb_players == 4)
		error(ERR_CHAMP_NBR, arena, av[index]);
	if (!(prog_header = malloc(sizeof(t_prog_header))))
		error(ERR_MALLOC, arena, NULL);
	player_ind = get_player_number(arena, number);
	if ((fd = open(av[index], O_RDONLY)) < 0)
	{
		free(prog_header);
		error(ERR_READING, arena, av[index]);
	}
	get_filename(arena, av[index], player_ind);
	if (read_pars_player(arena, fd, prog_header) == EXIT_FAILURE)
	{
		free(prog_header);
		error(ERR_MALLOC, arena, NULL);
	}
	get_player_name(arena, player_ind, prog_header);
	get_player_comment(arena, player_ind, prog_header);
	arena->players[player_ind].header_size = prog_header->size;
	ft_memdel((void**)&prog_header);
	arena->nb_players++;
}

/*
** check_number() - number checker
** @av:    Array of parameters
** @index: Index of param to check (av[index])
**
** If -n parameter is detect, check the param after -n and call check_player()
**
** Return: index avancement
*/

int					check_number(t_arena *arena, char **av, int index)
{
	int				i;
	int				number;

	i = 0;
	if (arena->nb_players > 4)
		error(ERR_CHAMP_NBR, arena, NULL);
	while (av[index][i])
	{
		if (ft_isdigit(av[index][i]) == 0)
			error(ERR_INDEX, arena, av[index]);
		i++;
	}
	number = ft_atoi(av[index]);
	if (number < 1 || number > 4 ||
		arena->players[number - 1].filename != NULL)
		error(ERR_INDEX, arena, av[index]);
	if (ft_strstr(av[index + 1], ".cor") == NULL)
		error(ERR_CHAMP_NAME, arena, av[index + 1]);
	check_player(arena, av, number, ++index);
	return (++index);
}

/*
** check_params() - parameters checker
** @av:    Array of parameters
** @index: Index of param to check (av[index])
**
** For each param check which kind it is and check it with
** corresponding function.
**
** Return: index avancement
*/

int					check_param(t_arena *arena, char **av, int ac, int index)
{
	if (ft_strequ(av[index], "-dump"))
	{
		if (index == ac - 1)
			error(ERR_USAGE, arena, NULL);
		check_dump(arena, av, ++index);
	}
	else if (ft_strequ(av[index], "-v"))
		arena->visu = 1;
	else if (ft_strequ(av[index], "-a"))
		arena->aff = 1;
	else if (ft_strequ(av[index], "-n"))
	{
		if (index == ac - 1 || index == ac - 2)
			error(ERR_USAGE, arena, NULL);
		check_number(arena, av, ++index);
		index++;
	}
	else if (ft_strstr(av[index], ".cor") != NULL)
		check_player(arena, av, -1, index);
	else
		error(ERR_PARAM, arena, av[index]);
	index++;
	return (index);
}

/*
** read_params() - browse parameters
** @ac: Number of parameters
** @av: Array of parameters
**
** Browse av[] (parameters) and check thems.
*/

void				read_params(int ac, char **av, t_arena *arena)
{
	int				count;

	count = 1;
	if (ac == 1)
		error(ERR_USAGE, arena, NULL);
	while (count <= ac - 1)
		count = check_param(arena, av, ac, count);
	if (arena->nb_players == 0)
		error(ERR_USAGE, arena, NULL);
}
