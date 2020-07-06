/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_num_symbols(int n)
{
	if (n >= 0)
		return (ft_num_digits(n));
	else
		return (ft_num_digits(n) + 1);
}

char			*ft_itoa(int n)
{
	char	*num;
	size_t	num_symbols;
	size_t	start;

	num_symbols = ft_num_symbols(n);
	if (!(num = ft_strnew(num_symbols)))
		return (NULL);
	if (n >= 0)
		start = 0;
	else
	{
		num[0] = '-';
		start = 1;
	}
	while (num_symbols != start)
	{
		num[num_symbols - 1] = '0' + ((n % 10) < 0 ? -(n % 10) : n % 10);
		n /= 10;
		num_symbols--;
	}
	return (num);
}
