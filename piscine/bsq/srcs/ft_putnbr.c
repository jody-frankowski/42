/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/08 16:54:31 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 17:39:30 by tiperoul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nbr, uint32_t padding)
{
	if (nbr > -10 && nbr < 0)
	{
		ft_putchar('-');
		nbr *= -1;
	}
	if (nbr >= 0 && nbr < 10)
	{
		while (padding--)
			ft_putchar('0');
		ft_putchar('0' + nbr);
	}
	else
	{
		ft_putnbr(nbr / 10, padding--);
		ft_putchar('0' + (nbr < 0 ? -(nbr % 10) : nbr % 10));
	}
}
