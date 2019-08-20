/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putwchar_fd.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/09 17:46:08 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 17:46:08 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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

void	ft_putwchar_fd(int c, int fd)
{
	int i;

	i = 3;
	while (i >= 0)
	{
		if (c >> (8 * i))
			ft_putchar_fd(c >> (8 * i), fd);
		i--;
	}
}
