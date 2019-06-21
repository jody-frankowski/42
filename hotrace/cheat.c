/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cheat.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 18:19:58 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 18:19:58 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		cheat(void)
{
	if (g_buf_ptr[g_buf_size - 5] == 0x0a && g_buf_ptr[g_buf_size - 4] == 0x0a)
	{
		if (g_buf_ptr[g_buf_size - 2] == 0x7f)
		{
			if (g_buf_ptr[g_buf_size - 3] == 0x7f)
			{
				write(1, "   \n", 4);
			}
			else
			{
				ft_putchar(g_buf_ptr[g_buf_size - 3] + 1);
				write(1, " \n", 2);
			}
		}
		else
		{
			ft_putchar(g_buf_ptr[g_buf_size - 3]);
			ft_putchar(g_buf_ptr[g_buf_size - 2] + 1);
			write(1, "\n", 1);
		}
		return (1);
	}
	return (0);
}
