/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_read_all.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/13 19:22:54 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/13 19:22:54 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"

/*
** ft_read_all - Reads as much as possible from a fd
** @fd: The file descriptor to read from
** @buf: The buffer to read in
**
** Sets @buf to point to the malloced memory containing the read.
**
** Return: the total number of bytes read or -1 on error
*/

int	ft_read_all(int fd, char **buf)
{
	char	tmp[BUFSIZ];
	ssize_t	read_size;
	ssize_t	total;

	if (!buf)
		return (-1);
	total = 0;
	while ((read_size = read(fd, tmp, BUFSIZ)) > 0)
	{
		total += read_size;
		if (!(*buf = ft_realloc(buf, total - read_size, total)))
			return (0);
	}
	if (read_size == -1)
		return (-1);
	else
		return (total);
}
