/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 18:19:58 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 18:19:58 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

#define BUFSIZE 134217728

void	ft_read_all(int fd)
{
	size_t		read_size;
	size_t		total;

	g_buf = malloc(sizeof(char) * (BUFSIZE + 16));
	g_buf_ptr = g_buf + 16;
	total = 0;
	while ((read_size = read(fd, g_buf_ptr + total, BUFSIZE - total)) > 0)
	{
		total += read_size;
	}
	g_buf_size = total;
}
