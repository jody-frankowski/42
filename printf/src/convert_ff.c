/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_ff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include "libprintf.h"
#include "libft.h"

/*
** Called with a fake precision that is one more than the true value.
** We do this so that round_float() has one more digit to round properly.
*/

void	append_fractional_part(long double num, t_conv conv)
{
	int num_fractional_digits_wanted;

	if (!conv.precision_flag)
		conv.precision = 6;
	num_fractional_digits_wanted = conv.precision + 1;
	if (conv.precision >= 1 || (conv.hash_flag && conv.precision == 0))
		append_nchar(g_second_part, '.', 1);
	num = num - (long long)num;
	if (num < 0)
		num = -num;
	while (num_fractional_digits_wanted)
	{
		num *= 10.0;
		num_fractional_digits_wanted--;
		append_nchar(g_second_part, (((unsigned int)num) % 10) + '0', 1);
	}
}

void	float_handle_sign(long double num, t_conv conv)
{
	int is_negative;

	is_negative = ft_signbit_ld(num);
	if (conv.space_flag && !conv.plus_flag && !is_negative)
		prepend_nchar(g_first_part, ' ', 1);
	else if (conv.plus_flag && !is_negative)
		prepend_nchar(g_first_part, '+', 1);
	else if (is_negative)
		prepend_nchar(g_first_part, '-', 1);
}

int		handle_inf_or_nan(long double num, t_conv conv)
{
	if (num == 1.0 / 0.0 || num == -(1.0 / 0.0))
	{
		ft_strcpy(g_second_part, conv.specifier == 'f' ? "inf" : "INF");
		float_handle_sign(num, conv);
		return (1);
	}
	else if (num != num)
	{
		ft_strcpy(g_second_part, conv.specifier == 'f' ? "nan" : "NAN");
		float_handle_sign(num, conv);
		return (1);
	}
	return (0);
}

void	round_float(void)
{
	int carry;
	int i;
	int digit;
	int second_to_last_digit;

	i = ft_strlen(g_second_part) - 1;
	digit = g_second_part[i] % '0';
	g_second_part[i--] = '\0';
	carry = 0;
	second_to_last_digit = g_second_part[i] == '.' ? g_second_part[i - 1] :
		g_second_part[i];
	if (digit >= 6 || (digit == 5 && second_to_last_digit % 2 == 1))
		carry = 1;
	while (carry && i != -1)
	{
		if (g_second_part[i] != '.')
		{
			carry = g_second_part[i] == '9' ? 1 : 0;
			g_second_part[i] = (((g_second_part[i] % '0') + 1) % 10) + '0';
		}
		i--;
	}
	if (carry)
		prepend_nchar(g_second_part, '1', 1);
}

/*
** convert_ff() - Convert a floating point number to a string
** @args: The variadic arguments
** @conv: The conversion flags and parameters
**
** Maximum length in characters of a double (64 bit):
** https://stackoverflow.com/a/1701272
**
** Return: The number of resulting characters on success. -1 on error.
**         Sets g_output to the result string.
*/

int		convert_ff(va_list args, t_conv conv)
{
	char		*tmp;
	long double	num;

	num = get_num_ld(args, conv);
	if (!allocate_globals(conv, 2048))
		return (-1);
	if (!handle_inf_or_nan(num, conv))
	{
		if (!(tmp = ft_ulltostr(num < 0 ? -num : num, "0123456789")))
			return (free_globals());
		ft_strcpy(g_second_part, tmp);
		free(tmp);
		append_fractional_part(num, conv);
		if (conv.space_flag && !conv.plus_flag && !ft_signbit_ld(num))
			prepend_nchar(g_first_part, ' ', 1);
		else if (conv.plus_flag && !ft_signbit_ld(num))
			prepend_nchar(g_first_part, '+', 1);
		else if (ft_signbit_ld(num))
			prepend_nchar(g_first_part, '-', 1);
		round_float();
	}
	pad_for_field_width(conv);
	cat_and_free();
	return (ft_strlen(g_output));
}
