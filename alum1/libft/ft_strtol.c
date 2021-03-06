/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtol.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/12 17:43:30 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/12 17:43:30 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

static int			ft_symbol_in_base(char c, int base)
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

static const char	*ft_treat_space_sign_base(const char **str, \
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

static int			ft_set_cutoff(unsigned long *cutoff, \
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
** unsigned long	result;
** unsigned long	cutoff;
** unsigned long	cutlim;
** unsigned long	neg;
** unsigned long	overflow;
** const char		*save;
** const char		*begin;
*/

long				ft_strtol(const char *str, char **endptr, int base)
{
	unsigned long	vars[5];
	const char		*tab[2];

	vars[4] = 0;
	tab[1] = ft_treat_space_sign_base(&str, &vars[3], &base, &tab[0]);
	vars[0] = ft_set_cutoff(&vars[1], &vars[2], base, vars[3]);
	while (*str && ft_symbol_in_base(*str, base) != -1)
	{
		if (!vars[4] && (vars[0] < vars[1] || (vars[0] == vars[1] && \
			(unsigned long)ft_symbol_in_base(*str, base) <= vars[2])))
		{
			vars[0] *= base;
			vars[0] += ft_symbol_in_base(*str, base);
		}
		else
			vars[4] = 1;
		str++;
	}
	if (vars[4])
		vars[0] = vars[3] ? LONG_MIN : LONG_MAX;
	else
		vars[0] = vars[3] ? -vars[0] : vars[0];
	if (endptr)
		*endptr = str == tab[1] ? (char *)tab[0] : (char *)str;
	return (vars[0]);
}
