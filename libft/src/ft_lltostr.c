/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltostr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static long long	calc_divisor(int num_digits, int base)
{
	long long	divisor;
	int			i;

	i = 0;
	divisor = 1;
	while (i < num_digits - 1)
	{
		divisor *= base;
		i++;
	}
	return (divisor);
}

/*
** ft_lltostr() - Convert a long long to a string in a certain base
** @num:          The long long to convert
** @base_charset: The characters to use in the conversion. This also
**                determines the base.
**
** Return: A pointer to the resultant string on success, or NULL on error.
*/

char				*ft_lltostr(long long num, char *base_charset)
{
	int				base;
	char			*converted;
	long long		divisor;
	unsigned int	i;
	size_t			num_digits;

	base = ft_strlen(base_charset);
	num_digits = ft_num_digits_ll(num, base);
	divisor = calc_divisor(num_digits, base);
	if (!(converted = malloc(num_digits + 1 + (num < 0 ? 1 : 0))))
		return (NULL);
	if (num < 0)
	{
		*converted++ = '-';
		divisor = -divisor;
	}
	i = 0;
	while (i < num_digits - 1)
	{
		converted[i++] = base_charset[(num / divisor) % base];
		divisor /= base;
	}
	converted[i++] = base_charset[(num % base) * (num < 0 ? -1 : 1)];
	converted[i++] = '\0';
	return (converted - (num < 0 ? 1 : 0));
}

/*
** ft_ulltostr() - Convert an unsigned long long to a string in a certain base
** @num:          The unsigned long long to convert
** @base_charset: The characters to use in the conversion. This also
**                determines the base.
**
** Return: A pointer to the resultant string on success, or NULL on error.
*/

char				*ft_ulltostr(unsigned long long num, char *base_charset)
{
	int					base;
	char				*converted;
	unsigned long long	divisor;
	unsigned int		i;
	size_t				num_digits;

	base = ft_strlen(base_charset);
	num_digits = ft_num_digits_ull(num, base);
	i = 0;
	divisor = 1;
	while (i++ < num_digits - 1)
		divisor *= base;
	if (!(converted = malloc(num_digits + 1)))
		return (NULL);
	i = 0;
	while (i < num_digits - 1)
	{
		converted[i++] = base_charset[(num / divisor) % base];
		divisor /= base;
	}
	converted[i++] = base_charset[num % base];
	converted[i++] = '\0';
	return (converted);
}
