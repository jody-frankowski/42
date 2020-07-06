/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:10:36 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/27 14:44:15 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** usage () - print usage corewar and exit program
*/

void	usage(void)
{
	ft_putstr("Usage : ./corewar [-v] [-dump NB] [-n NB] ");
	ft_putstr("player1.cor player2.cor player3.cor player4.cor\n");
	ft_putstr("        -v    : visualiser mode (ncurses)\n");
	ft_putstr("        -dump : stop VM and print memory at NB cycle\n");
	ft_putstr("        -n    : set number of next player, ");
	ft_putstr("remplace NB by wanted number between 1 and 4\n");
	exit(EXIT_FAILURE);
}

/*
** error() / error2() - print error and exit
** @reason: the reason of error
** @info:   infomartions about the reason of the error
**
** Print the error corresponding to @reason, free arena and exit
*/

void	error2(int reason, char *info)
{
	if (reason == ERR_READING)
		ft_printf("Error - Can't read champion : "BOLDWHITE" %s"RESET
		"\nThis file does not exist at specified path.\n", info);
	else if (reason == ERR_MALLOC)
		exit(EXIT_FAILURE);
	else if (reason == ERR_INS)
		ft_printf("Error - Invalid instruction : %s\n", info);
	else
		ft_printf("Error - Invalid parameter :"BOLDWHITE" %s"RESET"\n", info);
}

void	error(int reason, t_arena *arena, char *info)
{
	last_free(arena);
	if (reason == ERR_USAGE)
		usage();
	else if (reason == ERR_INDEX)
		ft_printf("Error - Bad index specified : "BOLDWHITE" %s"RESET
		"\nIndex must be between 1 and 4.\n%s\n", info,
		"2 champions can't have the same index");
	else if (reason == ERR_CHAMP_NAME)
		ft_printf("Error - Bad name specified : "BOLDWHITE" %s"RESET
		"\nChampion name must end by .cor.\n", info);
	else if (reason == ERR_CHAMP_COMMENT)
		ft_printf("Error - Invalid champion comment : "BOLDWHITE
		" %s"RESET"\n", info);
	else if (reason == ERR_CHAMP_NBR)
		ft_printf("Error - Too many champions, no more than 4 champions.\n");
	else if (reason == ERR_CHAMP_SIZE)
		ft_printf("Error - Champion's size is incorrect\n");
	else if (reason == ERR_PROG_HEADER_TOO_SMALL)
		ft_printf("Error - Champion's header is too small.\n");
	else if (reason == ERR_PROG_HEADER_WRONG_MAGIC_NUMBER)
		ft_printf("Error - Champion's magic number is wrong.\n");
	else
		error2(reason, info);
	usage();
}
