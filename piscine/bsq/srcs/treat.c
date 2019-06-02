/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   treat.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tiperoul <tiperoul@stud.le-101.fr>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/25 19:18:34 by tiperoul     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 23:34:39 by tiperoul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		treat3(int **grid, char *input, char *save, t_spec *spec)
{
	t_point	p;

	p.l = 0;
	p.c = 0;
	while (*input && p.l < spec->l)
	{
		if (!in_spec(*input, spec))
			return (0);
		if (*input == '\n')
		{
			p.l++;
			if (p.c != spec->c)
				return (0);
			p.c = -1;
		}
		else if (g_max.max < (grid[p.l][p.c] = neighbors(grid, save, spec, &p)))
		{
			g_max.max = grid[p.l][p.c];
			g_max.l = p.l;
			g_max.c = p.c;
		}
		p.c++;
		input++;
	}
	return (!(*input || p.l != spec->l));
}

/*
** malloc grid(int)
** validate + calc
*/

int		treat2(char *input, t_spec *spec)
{
	int		**grid;
	char	*save;

	save = input;
	if (!(grid = alloc_grid(spec)))
		return (0);
	g_max.l = 0;
	g_max.c = 0;
	g_max.max = 0;
	if (!treat3(grid, input, save, spec))
	{
		free_grid(grid, spec->l);
		return (0);
	}
	else
		free_grid(grid, spec->l);
	print_grid(input, spec);
	return (1);
}

/*
** read spec
** read first line of grid
*/

int		treat(char *input)
{
	t_spec		*spec;
	uint32_t	i;
	int			ret;

	if (!spec_valid(input))
		return (0);
	spec = get_spec(input);
	if (!spec)
		return (0);
	while (*input && *input != '\n')
		input++;
	if (!*input)
		return (0);
	input++;
	i = 0;
	while (input[i] && input[i] != '\n')
		i++;
	if (!input[i] || i == 0)
		return (0);
	spec->c = i;
	ret = treat2(input, spec);
	free(spec);
	return (ret);
}
