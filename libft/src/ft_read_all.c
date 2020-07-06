/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"

/*
** ft_read_all - Reads as much as possible from a fd
** @fd:  The file descriptor to read from
** @buf: The buffer to read in. *buf should be set to an already allocated
**       pointer or to NULL.
**
** Sets @buf to point to the malloced memory containing the read.
**
** Return: the total number of bytes read or -1 on error
*/

int	ft_read_all(int fd, char **buf)
{
	char	tmp[BUFSIZ];
	char	*new_buf;
	ssize_t	read_size;
	ssize_t	total;

	if (!buf)
		return (-1);
	total = 0;
	while ((read_size = read(fd, tmp, BUFSIZ)) > 0)
	{
		total += read_size;
		new_buf = ft_realloc(*buf, total - read_size, total);
		if (!new_buf)
			return (0);
		*buf = new_buf;
		ft_memcpy((*buf) + total - read_size, tmp, read_size);
	}
	if (read_size == -1)
		return (-1);
	else
		return (total);
}
