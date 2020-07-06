/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_check_players.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:10:45 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/27 18:34:18 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include "vm.h"

/*
** get_filename() - get player filename
** @filename:   Argument containing filename
** @player_ind: Index of concerned player
**
** Check @filename and store it in arena->players[@player_id].filename
*/

void		get_filename(t_arena *arena, char *filename, int player_id)
{
	int		index;
	int		filename_size;

	index = 0;
	filename_size = ft_strlen(filename);
	if (!(arena->players[player_id].filename = ft_strnew(filename_size)))
		error(ERR_MALLOC, arena, NULL);
	while (index < filename_size)
	{
		arena->players[player_id].filename[index] = filename[index];
		index++;
	}
}

/*
** get_player_nb() - get player number
** @number: Param after -n (= -1 if not -n)
**
** If there is not -n param, attribute automatically
** else return @number
**
** Return: player number
*/

int			get_player_number(t_arena *arena, int number)
{
	int		index;

	index = 0;
	if (number != -1)
	{
		arena->players[number - 1].number = -number;
		return (number - 1);
	}
	while (index < MAX_PLAYERS)
	{
		if (arena->players[index].number == 0)
			break ;
		index++;
	}
	arena->players[index].number = -index - 1;
	return (index);
}

/*
** read_pars_player() - read player and parse-it
** @fd:   Player file fd
** @buff: The buffer
** @prog_header: Header of player file
**
** Read the file and put it in @buff, get program header and check its size
*/

int			read_pars_player(t_arena *arena, int fd, t_prog_header *prog_header)
{
	char	*buff;
	int		error_ret;
	int		size;

	buff = NULL;
	size = ft_read_all(fd, &buff);
	close(fd);
	error_ret = get_prog_header(buff, size, prog_header);
	if (error_ret != ERR_OK)
	{
		free(buff);
		free(prog_header);
		error(error_ret, arena, NULL);
	}
	if (prog_header->size > CHAMP_MAX_SIZE ||
		prog_header->size != (size - sizeof(t_prog_header)))
	{
		free(buff);
		free(prog_header);
		error(ERR_CHAMP_SIZE, arena, NULL);
	}
	free(buff);
	return (EXIT_SUCCESS);
}

/*
** get_player_name() - Get the player name from prog_header
** @player_ind:  Index of concerned player
** @prog_header: Header of the concerned player
**
** Get the player name from prog_header and put it in player[@player_ind].name
*/

void		get_player_name(t_arena *arena, int player_ind,
	t_prog_header *prog_header)
{
	int		index;

	index = 0;
	while (index < PROG_NAME_LENGTH)
	{
		arena->players[player_ind].name[index] = prog_header->name[index];
		index++;
	}
	arena->players[player_ind].name[index] = '\0';
}

/*
** get_player_comment() - Get the player comment from prog_header
** @player_ind:  Index of concerned player
** @prog_header: Header of the concerned player
**
** Get the player comment from prog_header and put it
** in player[@player_ind].comment
*/

void		get_player_comment(t_arena *arena, int player_ind,
	t_prog_header *prog_header)
{
	int		index;

	index = 0;
	while (index < PROG_COMMENT_LENGTH)
	{
		arena->players[player_ind].comment[index] =
			prog_header->comment[index];
		index++;
	}
	arena->players[player_ind].comment[index] = '\0';
}
