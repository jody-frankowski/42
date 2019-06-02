/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   build.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/02 16:54:22 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/02 16:54:22 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "alcu.h"
#include "get_next_line.h"
#include "libft.h"
#include <stdlib.h>

int			alcu_get_matches(char *line)
{
	char *endptr;
	long matches;

	matches = ft_strtol(line, &endptr, 10);
	if (*endptr != '\0')
		return (0);
	if (matches < ALCU_MIN_MATCHES || matches > ALCU_MAX_MATCHES)
		return (0);
	return (matches);
}

t_game_type	game_type(int prev_line_should_start_first)
{
	if (prev_line_should_start_first)
		return (MISERE);
	else
		return (NORMAL);
}

int			should_start_first(t_line *line)
{
	if (line->game_type == MISERE)
	{
		if ((line->matches % 4) != 1)
			return (1);
		else
			return (0);
	}
	else
	{
		if ((line->matches % 4) != 0)
			return (1);
		else
			return (0);
	}
}

int			free_stuff(void *a, void *b)
{
	if (a)
		free(a);
	if (b)
		free(b);
	return (0);
}

int			alcu_buildboard(t_line **board, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (fd == 0 && ft_strlen(line) == 0 && !free_stuff(line, NULL))
			break ;
		if (!(*board = ft_realloc(*board, sizeof(**board) * i,
								sizeof(**board) * (i + 1))))
			return (free_stuff(*board, line));
		if (!((*board)[i].matches = alcu_get_matches(line)))
			return (free_stuff(*board, line));
		if (i == 0)
			(*board)[i].game_type = MISERE;
		else
			(*board)[i].game_type =
				game_type((*board)[i - 1].should_start_first);
		(*board)[i].should_start_first = should_start_first(&(*board)[i]);
		free(line);
		i++;
	}
	if (i < 1)
		return (free_stuff(*board, NULL));
	return (i);
}
