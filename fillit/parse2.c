/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/24 21:05:32 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/24 21:05:32 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "fillit.h"
#include "libft.h"

void	fill_hashes(char lines[4][5], int x, int y)
{
	if (y - 1 >= 0 && lines[(y - 1)][x] == '#')
	{
		lines[(y - 1)][x] = 0;
		fill_hashes(lines, x, y - 1);
	}
	if (y + 1 <= 3 && lines[(y + 1)][x] == '#')
	{
		lines[(y + 1)][x] = 0;
		fill_hashes(lines, x, y + 1);
	}
	if (x - 1 >= 0 && lines[y][x - 1] == '#')
	{
		lines[y][x - 1] = 0;
		fill_hashes(lines, x - 1, y);
	}
	if (x + 1 <= 3 && lines[y][x + 1] == '#')
	{
		lines[y][x + 1] = 0;
		fill_hashes(lines, x + 1, y);
	}
}

int		all_hashes_touch(const char lines[4][5])
{
	int		x;
	int		y;
	int		filled;
	char	copy[4][5];

	ft_memmove(copy, lines, TETRI_BLOCK_LEN);
	filled = 0;
	y = 0;
	while (y < T_TETRI_WIDTH)
	{
		x = 0;
		while (x < T_TETRI_WIDTH)
		{
			if (copy[y][x] == '#')
			{
				if (filled == 1)
					return (0);
				fill_hashes(copy, x, y);
				filled = 1;
			}
			x++;
		}
		y++;
	}
	return (1);
}

int		tetri_is_valid(const char lines[4][5])
{
	int	x;
	int	y;
	int	num_hashes;

	num_hashes = 0;
	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
		{
			if (lines[y][x] == '#')
				num_hashes++;
			else if (lines[y][x] != '.')
				return (0);
		}
		if (lines[y][4] != '\n')
			return (0);
	}
	if (!all_hashes_touch(lines))
		return (0);
	return (num_hashes == 4);
}
