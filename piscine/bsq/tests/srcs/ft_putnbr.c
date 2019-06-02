/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/08 16:54:31 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/08 16:54:32 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int fd, int nbr)
{
	long long	nb;

	nb = nbr;
	if (nb < 0)
	{
		ft_putchar_fd(fd, '-');
		nb *= -1;
	}
	if (nb < 10)
	{
		ft_putchar_fd(fd, '0' + nb);
	}
	else
	{
		ft_putnbr_fd(fd, nb / 10);
		ft_putchar_fd(fd, '0' + nb % 10);
	}
}
