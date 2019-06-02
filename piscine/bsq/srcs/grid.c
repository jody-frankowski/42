/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   grid.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 18:14:27 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 19:37:36 by tiperoul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

int		**alloc_grid(t_spec *spec)
{
	int			**grid;
	uint32_t	i;

	grid = (int **)malloc(sizeof(*grid) * spec->l);
	if (!grid)
		return (NULL);
	i = 0;
	while (i < spec->l)
	{
		grid[i] = (int *)malloc(sizeof(**grid) * spec->c);
		if (!grid[i])
		{
			free_grid(grid, i);
			return (NULL);
		}
		i++;
	}
	return (grid);
}

int		free_grid(int **grid, uint32_t l)
{
	uint32_t i;

	i = 0;
	while (i < l)
		free(grid[i++]);
	free(grid);
	return (1);
}

void	print_grid(char *input, t_spec *spec)
{
	int			i;
	t_point		topleft;
	int			topleft_ind;
	int			ind;

	topleft.l = g_max.l - g_max.max + 1;
	topleft.c = g_max.c - g_max.max + 1;
	topleft_ind = calc_coord(&topleft, spec);
	i = 0;
	while (i < g_max.max * g_max.max)
	{
		ind = topleft_ind + (i % g_max.max) + (i / g_max.max) * (spec->c + 1);
		input[ind] = spec->full;
		i++;
	}
	write(1, input, spec->l * (spec->c + 1));
}

void	print_int(int **grid, t_spec *spec)
{
	uint32_t i;
	uint32_t j;

	i = 0;
	while (i < spec->l)
	{
		j = 0;
		while (j < spec->c)
		{
			ft_putnbr(grid[i][j], 0);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
