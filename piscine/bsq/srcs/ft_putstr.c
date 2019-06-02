/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/10 14:44:36 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/10 14:44:41 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(int fd, char *str)
{
	while (*str)
		write(fd, str++, 1);
}

void	ft_putstr(char *str)
{
	ft_putstr_fd(1, str);
}
