/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_putwchar_fd - Writes an UTF-8 encoded character to a fd
** @c: The UTF-8 encoded character
** @fd: The file descriptor to write to
**
** Write the UTF-8 encoded character c to the file descriptor fd.
** If the character is encoded on multiple bytes, they should be
** on the least significant bytes in priority.
** Example: http://www.fileformat.info/info/unicode/char/1337/index.htm
** 0x00 0xE1 0x8C 0xB7
*/

void	ft_putwchar_fd(int fd, int c)
{
	int i;

	i = 3;
	while (i >= 0)
	{
		if (c >> (8 * i))
			ft_putchar_fd(fd, c >> (8 * i));
		i--;
	}
}
