/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "ft_errno.h"
#include "libft.h"

static int			symbol_in_base(char c, int base)
{
	int value;

	if (base < 2 || base > 36)
		return (-1);
	if (ft_isdigit(c))
		value = c - '0';
	else if (ft_isupper(c))
		value = c - 'A' + 10;
	else if (ft_islower(c))
		value = c - 'a' + 10;
	else
		return (-1);
	if (value < base)
		return (value);
	else
		return (-1);
}

static const char	*treat_space_sign_base(const char **str, \
											unsigned long *neg, \
											int *base, \
											const char **save)
{
	*save = (char *)*str;
	*str += ft_strspn(*str, "\t\n\r\v\f ");
	*neg = **str == '-' ? 1 : 0;
	**str == '-' || **str == '+' ? (*str)++ : *str;
	if (*base == 0 || *base == 16)
	{
		if (ft_strncasecmp("0x", *str, 2) == 0)
		{
			*base = 16;
			*str += 2;
		}
	}
	if (*base == 0)
	{
		if (ft_strncmp("0", *str, 1) == 0)
			*base = 8;
		else
			*base = 10;
	}
	return (*str);
}

static int			set_cutoff(unsigned long *cutoff, \
								unsigned long *cutlim, \
								int base, \
								unsigned long neg)
{
	*cutoff = neg ? LONG_MIN : LONG_MAX;
	*cutlim = *cutoff % base;
	*cutoff /= base;
	return (0);
}

/*
** ft_strtol - Converts a string to an integer
** @str: The string to convert
** @endptr: A pointer to the last valid digit
** @base: The radix to use
**
** The following are the variables the function should have, but can't because
** of the Norm. They are instead put in the vars and tab arrays, in the same
** order:
** unsigned long	result;
** unsigned long	cutoff;
** unsigned long	cutlim;
** unsigned long	neg;
** unsigned long	overflow;
** const char		*save;
** const char		*begin;
**
** Return: The result of the conversion. Or 0 if no conversion could be
** performed. Or LONG_MIN if there is an underflow, or LONG_MAX if there is an
** overflow, and errno is set to FT_ERANGE.
*/

long				ft_strtol(const char *str, char **endptr, int base)
{
	unsigned long	vars[5];
	const char		*tab[2];

	vars[4] = 0;
	tab[1] = treat_space_sign_base(&str, &vars[3], &base, &tab[0]);
	vars[0] = set_cutoff(&vars[1], &vars[2], base, vars[3]);
	while (*str && symbol_in_base(*str, base) != -1)
	{
		if (!vars[4] && (vars[0] < vars[1] || (vars[0] == vars[1] && \
			(unsigned long)symbol_in_base(*str, base) <= vars[2])))
		{
			vars[0] *= base;
			vars[0] += symbol_in_base(*str, base);
		}
		else
			vars[4] = 1;
		str++;
	}
	if (vars[4] && (g_errno = FT_ERANGE))
		vars[0] = vars[3] ? LONG_MIN : LONG_MAX;
	else
		vars[0] = vars[3] ? -vars[0] : vars[0];
	if (endptr)
		*endptr = str == tab[1] ? (char *)tab[0] : (char *)str;
	return (vars[0]);
}
