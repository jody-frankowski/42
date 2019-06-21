/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 18:19:58 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 18:19:58 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

inline void	print(char *str, size_t n)
{
	if (g_print_buf_size < PRINT_BUF_SIZE - n)
	{
		ft_memcpy(g_print_buf + g_print_buf_size, str, n);
		g_print_buf_size += n;
	}
	else
	{
		write(1, g_print_buf, g_print_buf_size);
		ft_memcpy(g_print_buf, str, n);
		g_print_buf_size = n;
	}
}

inline void	print_flush(void)
{
	write(1, g_print_buf, g_print_buf_size);
}

inline void	print_data(char *data, uint8_t length)
{
	if (data)
	{
		print(data, *(data - 1) & 0b01111111);
		print("\n", 1);
	}
	else
	{
		print(g_buf_ptr - length, length);
		print(": Not found.\n", 13);
	}
}
