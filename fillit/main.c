/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/24 20:37:56 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/24 20:37:56 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "fillit.h"
#include "libft.h"

void	error(int fd)
{
	ft_putstr("error\n");
	close(fd);
	exit(1);
}

void	usage(char *program_name)
{
	ft_putstr(program_name);
	ft_putstr(": input_file\n");
}

int		solve(void)
{
	int done;

	g_width = 2;
	while (g_width * g_width < g_num_tetris * 4)
		g_width++;
	while (!(done = place_tetris(0)) && g_width < 17)
		g_width++;
	if (!done)
	{
		init_17();
		while (!place_tetris_17(0))
			g_width++;
	}
	return (print_map());
}

int		main(int argc, char **argv)
{
	int		fd;

	if (argc != 2)
	{
		usage(argv[0]);
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			error(fd);
		if (!parse_input(fd))
			error(fd);
		if (!solve())
			error(fd);
		close(fd);
	}
}
