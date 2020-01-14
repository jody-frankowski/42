/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   grid.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/06 00:43:56 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/06 00:43:56 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "filler.h"
#include "gnl.h"
#include "libft.h"

int		read_grid_size(t_grid *grid)
{
	char *line;
	char *bak;

	line = NULL;
	if (ft_gnl(0, &line) <= 0)
		return (0);
	bak = line;
	line = ft_strchr(line, ' ') + 1;
	grid->y = ft_strtol(line, &line, 10);
	line++;
	grid->x = ft_strtol(line, &line, 10);
	if (*line != ':' || grid->x == 0 || grid->y == 0)
	{
		free(bak);
		return (0);
	}
	free(bak);
	return (1);
}

int		read_grid(t_grid *grid, int is_map)
{
	char	*line;
	int		i;

	if (is_map)
	{
		line = NULL;
		if (ft_gnl(0, &line) <= 0)
			return (0);
		free(line);
	}
	i = 0;
	while (i < grid->y)
	{
		line = NULL;
		if (ft_gnl(0, &line) <= 0)
			return (0);
		if (is_map)
			ft_memcpy(grid->grid + i * grid->x,
					ft_strchr(line, ' ') + 1, grid->x);
		else
			ft_memcpy(grid->grid + i * grid->x, line, grid->x);
		free(line);
		i++;
	}
	return (1);
}

char	get_grid_cell(t_grid grid, int x, int y)
{
	return (*(grid.grid + y * grid.x + x));
}
