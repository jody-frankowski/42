/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_up_to.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
** ft_read_up_to - Read up to a certain number of bytes
** @fd: File descriptor to read from
** @buff: Pointer to the buffer to read in
** @to_read: Number of bytes to read
** @total: Pointer that will be set to the number of bytes read
**
** ft_read_up_to tries to read up to @to_read bytes. This is a convenient
** wrapper around read(2) when trying to read from a pipe for example. Usually
** when reading from a pipe you have no guarantees about the number of bytes
** that will be read, while with this function you can be sure that @to_read
** bytes will be read if it's at all possible.
**
** Return: 1 on success. 0 on eof. -1 on error.
*/

int	ft_read_up_to(int fd, char *buff, int to_read, int *total)
{
	int ret;

	*total = 0;
	while ((ret = read(fd, buff + *total, to_read - *total)) > 0)
		*total += ret;
	if (ret == -1 || ret == 0)
		return (ret);
	return (1);
}
