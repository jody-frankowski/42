/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   player.c                                         .::    .:/ .      .::   */
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

t_coord	get_player_coords(t_grid map, t_player player)
{
	t_coord coords;

	coords.y = 0;
	while (coords.y < map.y)
	{
		coords.x = 0;
		while (coords.x < map.x)
		{
			if (get_grid_cell(map, coords.x, coords.y) == player.symbol)
				return (coords);
			coords.x++;
		}
		coords.y++;
	}
	return (coords);
}

int		read_players_infos(t_player *player, t_player *enemy)
{
	char *line;

	line = NULL;
	if (ft_gnl(0, &line) <= 0)
		return (0);
	if (line[10] == '1')
	{
		player->symbol = 'O';
		enemy->symbol = 'X';
	}
	else
	{
		player->symbol = 'X';
		enemy->symbol = 'O';
	}
	free(line);
	return (1);
}
