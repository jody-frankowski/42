/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cat.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/19 13:23:34 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/19 13:23:35 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include "ft_errno.h"
#include "libft.h"

#define BUF_SIZE 4096

void	print_error(char *msg)
{
	ft_putstr(2, "ft_cat: ");
	ft_putstr(2, msg);
	ft_putstr(2, ": ");
	ft_putstr(2, g_errors[errno]);
	ft_putstr(2, "\n");
}

int		ft_cat(int fd)
{
	int		ret;
	char	buf[BUF_SIZE];

	while ((ret = read(fd, buf, BUF_SIZE)) > 0)
		write(1, buf, ret);
	return (ret);
}

int		ft_read_stdin_and_cat(void)
{
	int		ret;
	char	buf[BUF_SIZE];

	while ((ret = read(0, buf, BUF_SIZE)) > 0)
		write(1, buf, ret);
	if (ret == -1)
	{
		print_error("stdin");
		return (1);
	}
	return (0);
}

int		ft_open_and_cat(char *file)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_error(file);
		return (1);
	}
	if (ft_cat(fd) == -1)
	{
		print_error(file);
		return (1);
	}
	if (close(fd) == -1)
	{
		print_error(file);
		return (1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	int ret;

	ac--;
	av++;
	ret = 0;
	if (ac == 0)
		ret = ret | ft_read_stdin_and_cat();
	else
	{
		while (ac-- > 0)
		{
			if (ft_strcmp(*av, "-") == 0)
				ret = ret | ft_read_stdin_and_cat();
			else
				ret = ret | ft_open_and_cat(*av);
			av++;
		}
	}
	return (ret);
}
