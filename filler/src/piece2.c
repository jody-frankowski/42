/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   piece2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/06 00:43:56 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/06 00:43:56 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

int		is_in_grid_range(t_grid grid, int x, int y)
{
	return (x >= 0 && x < grid.x && y >= 0 && y < grid.y);
}

int		piece_can_be_placed(
	t_grid piece,
	t_grid map,
	t_coord coord,
	t_player player
)
{
	int		player_cells_covered;
	int		x;
	int		y;
	char	map_cell;

	player_cells_covered = 0;
	y = -1;
	while (++y < piece.y)
	{
		x = -1;
		while (++x < piece.x)
		{
			if (get_grid_cell(piece, x, y) == PIECE_SYM)
			{
				if (!is_in_grid_range(map, coord.x + x, coord.y + y))
					return (0);
				map_cell = get_grid_cell(map, coord.x + x, coord.y + y);
				if (map_cell == player.symbol)
					player_cells_covered++;
				else if (map_cell != MAP_EMPTY_SYM)
					return (0);
			}
		}
	}
	return (player_cells_covered == 1);
}

t_coord	get_clsest_cell(
	t_grid piece,
	t_coord placement,
	t_coord target,
	t_grid map
)
{
	t_coord closest;
	t_coord cell;

	closest.x = map.x * 2;
	closest.y = map.y * 2;
	cell.y = placement.y;
	while (cell.y - placement.y < piece.y)
	{
		cell.x = placement.x;
		while (cell.x - placement.x < piece.x)
		{
			if (get_grid_cell(piece, cell.x - placement.x, cell.y - placement.y)
				== PIECE_SYM)
			{
				if (distance(cell, target) < distance(closest, target))
					closest = cell;
			}
			cell.x++;
		}
		cell.y++;
	}
	return (closest);
}

void	init_cell_and_placement(
	t_grid map,
	t_coord *best_cell,
	t_coord *best_placement
)
{
	best_cell->x = map.x * 2;
	best_cell->y = map.y * 2;
	best_placement->x = 0;
	best_placement->y = 0;
}

t_coord	choose_piece_placement(
	t_grid piece,
	t_grid map,
	t_strategy strat,
	t_player player
)
{
	t_coord best_cell;
	t_coord best_placement;
	t_coord coord;
	t_coord closest_cell;

	init_cell_and_placement(map, &best_cell, &best_placement);
	coord.y = 0 - piece.y - 1;
	while (++(coord.y) < map.y)
	{
		coord.x = 0 - piece.x - 1;
		while (++(coord.x) < map.x)
		{
			if (piece_can_be_placed(piece, map, coord, player))
			{
				closest_cell = get_clsest_cell(piece, coord, strat.target, map);
				if (distance(closest_cell, strat.target) <
					distance(best_cell, strat.target))
				{
					best_cell = closest_cell;
					best_placement = coord;
				}
			}
		}
	}
	return (best_placement);
}
