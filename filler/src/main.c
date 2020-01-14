/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/06 17:43:30 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/06 17:43:30 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "filler.h"

int	init_players_map_strat(
	t_player *player,
	t_player *enemy,
	t_grid *map,
	t_strategy *strat
)
{
	if (!read_players_infos(player, enemy))
		return (0);
	if (!init_map(map))
		return (0);
	init_strat(strat, *map, *enemy);
	return (1);
}

int	free_map_and_piece(t_grid map, t_grid piece)
{
	free(map.grid);
	free(piece.grid);
	return (0);
}

int	main(void)
{
	t_grid		map;
	t_player	player;
	t_player	enemy;
	t_grid		piece;
	t_strategy	strat;

	if (!init_players_map_strat(&player, &enemy, &map, &strat))
		return (1);
	while (1)
	{
		if (!read_piece(&piece))
		{
			free(map.grid);
			return (0);
		}
		if (!place_piece(choose_piece_placement(piece, map, strat, player)))
			return (free_map_and_piece(map, piece));
		free(piece.grid);
		if (!read_map(&map))
		{
			free(map.grid);
			return (0);
		}
	}
	return (0);
}
