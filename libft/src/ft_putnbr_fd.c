/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
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
