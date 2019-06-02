/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_tail.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/19 18:30:54 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/19 18:30:55 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include "ft_errno.h"
#include "libft.h"

#define BUF_SIZE 4096

int		print_error(char *msg)
{
	ft_putstr(2, "ft_tail: ");
	ft_putstr(2, msg);
	ft_putstr(2, ": ");
	ft_putstr(2, g_errors[errno]);
	ft_putstr(2, "\n");
	return (1);
}

int		ft_len_file(char *file)
{
	int		fd;
	int		len;
	int		ret;
	char	buf[BUF_SIZE];

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_error(file);
		return (-1);
	}
	len = 0;
	while ((ret = read(fd, buf, BUF_SIZE)) > 0)
		len += ret;
	if (ret == -1)
	{
		print_error(file);
		return (-1);
	}
	if (close(fd) == -1)
	{
		print_error(file);
		return (-1);
	}
	return (len);
}

int		ft_tail(int fd, int head, int len, int bytes)
{
	int		ret;
	char	buf[BUF_SIZE];

	if (head)
	{
		while ((ret = read(fd, buf, (bytes - 1) % BUF_SIZE)) > 0)
			bytes -= ret;
		if (ret == -1)
			return (-1);
		while ((ret = read(fd, buf, BUF_SIZE)) > 0)
			write(1, buf, ret);
		if (ret == -1)
			return (-1);
		return (0);
	}
	while ((ret = read(fd, buf, (len - bytes) % BUF_SIZE)) > 0)
		len -= ret;
	if (ret == -1)
		return (-1);
	while ((ret = read(fd, buf, bytes % BUF_SIZE)) > 0)
	{
		write(1, buf, ret);
		bytes -= ret;
	}
	return (ret);
}

int		ft_open_and_tail(char *file, int head, int bytes)
{
	int fd;
	int len;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_error(file));
	len = 0;
	if (!head)
	{
		len = ft_len_file(file);
		if (len == -1)
			return (print_error(file));
	}
	if (ft_tail(fd, head, len, bytes) == -1)
		return (print_error(file));
	if (close(fd) == -1)
		return (print_error(file));
	return (0);
}

int		main(int ac, char **av)
{
	int bytes_count;
	int head;
	int ret;

	ac -= 2;
	av += 2;
	head = *av[0] == '+' ? 1 : 0;
	bytes_count = ft_atoi(*av);
	bytes_count = bytes_count < 0 ? -bytes_count : bytes_count;
	ac--;
	av++;
	ret = 0;
	while (ac-- > 0)
	{
		ret = ret | ft_open_and_tail(*av, head, bytes_count);
		av++;
	}
	return (ret);
}
