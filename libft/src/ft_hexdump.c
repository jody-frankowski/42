/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include "libft.h"

/*
** ft_hexdump - Print a basic hexdump
** @ptr: Pointer to the memory to print
** @len: How much bytes to print
*/

void	ft_hexdump(const void *ptr, size_t len)
{
	ft_hexdump_fd(1, ptr, len);
}

/*
** ft_hexdump_fd - Print a basic hexdump to a file descriptor
** @fd:  File descriptor to print to
** @ptr: Pointer to the memory to print
** @len: How much bytes to print
*/

void	ft_hexdump_fd(int fd, const void *ptr, size_t len)
{
	size_t			i;
	size_t			j;
	const t_byte	*mem = ptr;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < HEXDUMP_WIDTH && i + j < len)
		{
			dprintf(fd, "%02hhx ", mem[i + j]);
			j++;
		}
		j = 0;
		while (j < HEXDUMP_WIDTH && i + j < len)
		{
			if (isprint(mem[i + j]))
				dprintf(fd, "%c", mem[i + j]);
			else
				dprintf(fd, ".");
			j++;
		}
		dprintf(fd, "\n");
		i += HEXDUMP_WIDTH;
	}
}
