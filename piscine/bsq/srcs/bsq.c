/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bsq.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 11:49:21 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 23:24:45 by tiperoul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

int g_error = 0;

void	error(void)
{
	g_error = -1;
	write(2, "map error\n", 10);
}

char	*read_input(int fd)
{
	int		ret;
	size_t	size;
	char	buf[BUF_SIZE + 1];
	char	*input;

	size = 0;
	input = NULL;
	size = read(fd, buf, 64);
	buf[size] = '\0';
	input = (char*)ft_realloc(input, size + 1);
	if (!input || !spec_valid(buf))
		return (0);
	ft_strcat(input, buf);
	while ((ret = read(fd, buf, BUF_SIZE)) > 0)
	{
		size += ret;
		buf[ret] = '\0';
		input = (char*)ft_realloc(input, size + 1);
		if (!input)
			return (NULL);
		ft_strcat(input, buf);
	}
	if (ret == -1)
		return (NULL);
	return (input);
}

char	*open_read(int ac, char **av)
{
	int		fd;
	char	*input;

	fd = 0;
	input = NULL;
	if (ac && (fd = open(*av, O_RDONLY)) == -1)
		return (NULL);
	else
	{
		input = read_input(fd);
		close(fd);
	}
	return (input);
}

int		main(int ac, char **av)
{
	int		i;
	char	*input;

	i = 0;
	ac--;
	av++;
	while (i < ac || ac == 0)
	{
		input = open_read(ac, av + i);
		if (input)
		{
			if (!treat(input))
				error();
			free(input);
			i < ac - 1 ? write(1, "\n", 1) : 1;
		}
		else
		{
			error();
			i < ac - 1 ? write(1, "\n", 1) : 1;
		}
		ac == 0 ? ac = -1 : ac;
		i++;
	}
	return (g_error);
}
