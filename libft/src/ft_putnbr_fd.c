/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_fd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/07 16:40:44 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 16:40:44 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int fd, int n)
{
	int		pow;
	size_t	num_digits;
	size_t	digit;

	num_digits = ft_num_digits(n);
	pow = ft_pow(10, num_digits - 1);
	if (n < 0)
		ft_putchar_fd(fd, '-');
	while (pow)
	{
		digit = (n / pow) % 10 < 0 ? -((n / pow) % 10) : (n / pow) % 10;
		ft_putchar_fd(fd, '0' + digit);
		pow /= 10;
	}
}
