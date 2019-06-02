/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   coord.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 18:18:15 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 19:36:22 by tiperoul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		calc_coord(t_point *p, t_spec *spec)
{
	return (p->l * (spec->c + 1) + p->c);
}

int		neighbors(int **grid, char *input, t_spec *spec, t_point *p)
{
	int min;

	if (input[calc_coord(p, spec)] == spec->obstacle)
		return (0);
	if (p->l == 0 || p->c == 0)
		return (1);
	min = ft_min(grid[p->l - 1][p->c],
					grid[p->l - 1][p->c - 1],
					grid[p->l][p->c - 1]);
	return (min + 1);
}
