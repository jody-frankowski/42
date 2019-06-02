/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jde-la-m <jde-la-m@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/29 22:08:10 by jde-la-m     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/02 23:26:23 by jde-la-m    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "alcu.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char	g_success_messages[][250] =
{
	GREE"\nYou won... did you cheat?\n"RSET,
	RED"\nI win! No suprise here.\n"RSET
};

char	g_start_messages[][30] =
{
	"\nI'll start then!\n",
	"\nAlright, you can start!\n",
};

int	alcu_validate_user_input(int line_matches, char *user_input)
{
	int matches;

	matches = alcu_get_matches(user_input);
	if (matches == 0)
		return (0);
	if (matches < ALCU_TURN_MIN_MATCHES || matches > ALCU_TURN_MAX_MATCHES ||
		matches > line_matches)
		return (0);
	return (matches);
}

int	alcu_play(t_line *board, int num_lines, t_player turn_for)
{
	int matches_to_rmv;

	matches_to_rmv = 0;
	while (num_lines > 0)
	{
		ft_putstr(ANSI_CLR_SCREEN);
		alcu_show_matches_to_remove(board, num_lines);
		if (matches_to_rmv)
		{
			ft_putstr(GREE"I have removed ");
			ft_putnbr(matches_to_rmv);
			ft_putstr(" match(es).\n\n");
		}
		else
			ft_putstr("\n\n");
		if (!(matches_to_rmv = alcu_matches_to_rmv(board, num_lines, turn_for)))
			return (0);
		board[num_lines - 1].matches -= matches_to_rmv;
		if (board[num_lines - 1].matches == 0)
			num_lines--;
		turn_for = (turn_for + 1) % (MAX + 1);
	}
	turn_for = (turn_for + 1) % (MAX + 1);
	ft_putstr(g_success_messages[turn_for]);
	return (1);
}

int	alcu_start(t_line *board, int num_lines)
{
	char		*user_input;
	t_player	first;

	first = -1;
	while (1)
	{
		ft_putstr(LYEL"\nDo you want to start? [y/n]: "RSET);
		if (get_next_line(0, &user_input) == 1)
		{
			if (ft_strcasecmp(user_input, "y") == 0)
				first = USER;
			else if (ft_strcasecmp(user_input, "n") == 0)
				first = AI;
			free(user_input);
			if (first == AI || first == USER)
				break ;
		}
		else
			return (0);
		ft_putstr(ANSI_CURSOR_UP);
		ft_putstr(ANSI_CURSOR_UP);
		ft_putstr(ANSI_CLR_LINE);
	}
	ft_putendl(g_start_messages[first]);
	return (alcu_play(board, num_lines, first));
}

int	main(int argc, char **argv)
{
	int		fd;
	int		num_lines;
	t_line	*board;

	if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = -1;
	if (fd == -1)
	{
		alcu_print_error();
		return (-1);
	}
	board = NULL;
	if (!(num_lines = alcu_buildboard(&board, fd)))
	{
		alcu_print_error();
		return (-1);
	}
	alcu_print_header(board, num_lines);
	alcu_start(board, num_lines);
	free(board);
	return (0);
}
