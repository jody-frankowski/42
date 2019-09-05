/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/24 21:10:15 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/24 21:10:15 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

int		is_same_tetri(t_tetri *a, t_tetri *b)
{
	return (*((uint64_t*)a->tetri) == *((uint64_t*)b->tetri));
}

int		is_same_tetri_17(t_tetri_17 *a, t_tetri_17 *b)
{
	return (*((__int128*)a->tetri) == *((__int128*)b->tetri));
}

void	set_same_tetri_17(t_tetri_17 *tetri, int i)
{
	while (i >= 0)
	{
		if (is_same_tetri_17(tetri, &(g_tetris_17[i])))
		{
			tetri->previous_same = &(g_tetris_17[i]);
			return ;
		}
		i--;
	}
}

void	init_17(void)
{
	int i;
	int j;

	i = 0;
	while (i < g_num_tetris)
	{
		j = 0;
		while (j < T_TETRI_WIDTH)
		{
			g_tetris_17[i].tetri[j] = g_tetris[i].tetri[j];
			j++;
		}
		g_tetris_17[i].height = g_tetris[i].height;
		g_tetris_17[i].width = g_tetris[i].width;
		set_same_tetri_17(&(g_tetris_17[i]), i - 1);
		i++;
	}
}
