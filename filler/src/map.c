/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map.c                                            .::    .:/ .      .::   */
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

int	init_map(t_grid *map)
{
	if (!read_grid_size(map))
		return (0);
	if (!(map->grid = malloc(sizeof(char) * map->x * map->y)))
		return (0);
	if (!read_grid(map, 1))
	{
		free(map->grid);
		return (0);
	}
	return (1);
}

int	read_map(t_grid *map)
{
	if (!read_grid_size(map))
		return (0);
	if (!read_grid(map, 1))
		return (0);
	return (1);
}
