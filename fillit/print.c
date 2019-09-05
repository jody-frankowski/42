/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/22 17:55:05 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/22 17:55:05 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "fillit.h"
#include "libft.h"

char	*init_print_map(void)
{
	char	*print_map;
	int		i;

	if (!(print_map = malloc(sizeof(char) * (g_width + 1) * g_width)))
		return (NULL);
	i = 0;
	while (i < g_width * (g_width + 1))
	{
		if (i % (g_width + 1) == g_width)
			print_map[i] = '\n';
		else
			print_map[i] = '.';
		i++;
	}
	return (print_map);
}

void	write_tetri(char *print_map, t_tetri *tetri, char c)
{
	int		x;
	int		y;

	y = 0;
	while (y < T_TETRI_WIDTH)
	{
		x = 0;
		while (x < T_TETRI_WIDTH)
		{
			if (((tetri->tetri[y] >> x) & 1) == 1)
			{
				print_map[
					((tetri->coord.y + y) * (g_width + 1)) + tetri->coord.x + x
					] = c;
			}
			x++;
		}
		y++;
	}
}

int		print_map(void)
{
	char	*print_map;
	int		i;

	if (!(print_map = init_print_map()))
		return (0);
	i = 0;
	while (i < g_num_tetris)
	{
		write_tetri(print_map, &(g_tetris[i]), 'A' + i);
		i++;
	}
	write(1, print_map, (g_width + 1) * g_width);
	free(print_map);
	return (1);
}
