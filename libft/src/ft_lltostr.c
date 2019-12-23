/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lltostr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/22 17:43:30 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/22 17:43:30 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int			ft_num_digits_base(long long num, int base)
{
	int num_digits;

	if (num == 0)
		return (1);
	num_digits = 0;
	while (num)
	{
		num /= base;
		num_digits++;
	}
	return (num_digits);
}

static int			ft_num_digits_base_u(unsigned long long num, int base)
{
	int num_digits;

	if (num == 0)
		return (1);
	num_digits = 0;
	while (num)
	{
		num /= base;
		num_digits++;
	}
	return (num_digits);
}

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
	int			base;
	char		*converted;
	long long	divisor;
	int			i;
	int			num_digits;

	base = ft_strlen(base_charset);
	num_digits = ft_num_digits_base(num, base);
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
	int					i;
	int					num_digits;

	base = ft_strlen(base_charset);
	num_digits = ft_num_digits_base_u(num, base);
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
