/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   solve.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/12 18:19:43 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/12 18:19:43 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

int		tetri_can_be_placed_17(uint8_t x, uint8_t y, t_tetri_17 *tetri)
{
	return ((*((__int128*)(g_map + y)) & *((__int128*)tetri->tetri) << x) == 0);
}

void	place_tetri_17(uint8_t x, uint8_t y, t_tetri_17 *tetri)
{
	*((__int128*)(g_map + y)) ^= *((__int128*)tetri->tetri) << x;
	tetri->coord.x = x;
	tetri->coord.y = y;
}

void	remove_tetri_17(uint8_t x, uint8_t y, t_tetri_17 *tetri)
{
	*((__int128*)(g_map + y)) ^= *((__int128*)tetri->tetri) << x;
}

int		try_place_tetri_17(int i, uint8_t x, uint8_t y, t_tetri_17 *tetri)
{
	if (tetri_can_be_placed_17(x, y, tetri))
	{
		place_tetri_17(x, y, tetri);
		if (place_tetris_17(i + 1))
			return (1);
		else
			remove_tetri_17(x, y, tetri);
	}
	return (0);
}

int		place_tetris_17(int i)
{
	uint8_t			x;
	uint8_t			y;
	uint8_t			first_run;
	t_tetri_17		*tetri;

	if (i == g_num_tetris)
		return (1);
	tetri = &(g_tetris_17[i]);
	first_run = 1;
	y = tetri->previous_same ? tetri->previous_same->coord.y +
		(tetri->previous_same->coord.x + 1) / g_width : 0;
	while (g_width - y >= tetri->height)
	{
		x = first_run && tetri->previous_same ?
			(tetri->previous_same->coord.x + 1) % g_width : 0;
		first_run = 0;
		while (g_width - x >= tetri->width)
		{
			if (try_place_tetri_17(i, x, y, tetri))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
