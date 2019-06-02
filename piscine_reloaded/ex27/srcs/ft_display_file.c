/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_display_file.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 12:18:49 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 12:18:50 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 4096

void	ft_putstr(int fd, char *str)
{
	while (*str)
		write(fd, str++, 1);
}

void	ft_cat(char *file)
{
	int		fd;
	int		ret;
	char	buf[BUF_SIZE];

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return ;
	while ((ret = read(fd, buf, BUF_SIZE)))
		write(1, buf, ret);
	close(fd);
}

int		main(int ac, char **av)
{
	if (ac < 2)
	{
		ft_putstr(2, "File name missing.\n");
		return (-1);
	}
	if (ac > 2)
	{
		ft_putstr(2, "Too many arguments.\n");
		return (-1);
	}
	ft_cat(av[1]);
	return (0);
}
