/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/19 20:49:42 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/19 20:49:42 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "fillit.h"
#include "libft.h"

t_point	get_tetri_top_left_coord(const char lines[4][5])
{
	int start_x;
	int start_y;
	int x;
	int y;

	start_x = 3;
	start_y = -1;
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (lines[y][x] == '#')
			{
				if (x < start_x)
					start_x = x;
				if (start_y == -1)
					start_y = y;
			}
			x++;
		}
		y++;
	}
	return ((t_point){start_x, start_y});
}

void	set_same_tetri(t_tetri *tetri)
{
	int i;

	i = g_num_tetris - 1;
	while (i >= 0)
	{
		if (is_same_tetri(tetri, &(g_tetris[i])))
		{
			tetri->previous_same = &(g_tetris[i]);
			return ;
		}
		i--;
	}
}

void	add_t_tetri(const char lines[4][5], t_point top_left)
{
	int		x;
	int		y;
	int		max_height;
	int		max_width;

	max_height = 0;
	max_width = 0;
	y = -1;
	while (++y + top_left.y < 4)
	{
		x = -1;
		while (++x + top_left.x < 4)
		{
			if (lines[(y + top_left.y)][x + top_left.x] == '#')
			{
				g_tetris[g_num_tetris].tetri[y] |= 1 << x;
				if (y + 1 > max_height)
					max_height = y + 1;
				if (x + 1 > max_width)
					max_width = x + 1;
			}
		}
	}
	g_tetris[g_num_tetris].height = max_height;
	g_tetris[g_num_tetris].width = max_width;
}

int		handle_tetri_input(char lines[4][5], int bytes_read)
{
	if (bytes_read != TETRI_BLOCK_LEN)
		return (0);
	if (tetri_is_valid(lines))
	{
		add_t_tetri(lines, get_tetri_top_left_coord(lines));
		set_same_tetri(&g_tetris[g_num_tetris]);
		g_num_tetris++;
        if (g_num_tetris == 27)
            return (0);
	}
	else
		return (0);
	return (1);
}

int		parse_input(int fd)
{
	char	lines[4][5];
	int		bytes_read;
	int		expects_new_block;
	int		error;

	expects_new_block = 1;
	while ((error = ft_read_up_to(fd, (char *)lines,
			TETRI_BLOCK_LEN, &bytes_read)) != -1 && bytes_read > 0)
	{
		expects_new_block = 0;
		if (!handle_tetri_input(lines, bytes_read))
			return (0);
		error = read(fd, lines, 1);
		if ((error == 1 && ((char *)lines)[0] != '\n') || error == -1)
			return (0);
		if (error == 1)
			expects_new_block = 1;
	}
	if (error == -1 || expects_new_block)
		return (0);
	return (1);
}
