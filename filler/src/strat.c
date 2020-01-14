/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   strat.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/06 00:43:56 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/06 00:43:56 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

void	init_strat(t_strategy *strat, t_grid map, t_player enemy)
{
	t_coord them;

	them = get_player_coords(map, enemy);
	strat->target = them;
}
