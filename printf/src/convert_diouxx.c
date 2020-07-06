/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_diouxx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libprintf.h"
#include "libft.h"

/*
** convert_di() - Convert a signed integer to a string in decimal
** @args: The variadic arguments
** @conv: The conversion flags and parameters
**
** /!\ A two's complement architecture is assumed because we get the absolute
** value of a number with the following formula: ~number + 1
**
** Return: The number of resulting characters on success. -1 on error.
**         Sets g_output to the result string.
*/

int	convert_di(va_list args, t_conv conv)
{
	char		*tmp;
	long long	num;

	num = get_num_ll(args, conv);
	if (!allocate_globals(conv, ft_num_digits_ll(num, get_base(conv))))
		return (-1);
	if (!(tmp = ft_ulltostr(num < 0 ? ~num + 1 : num, "0123456789")))
		return (free_globals());
	ft_strcpy(g_second_part, tmp);
	free(tmp);
	if (conv.precision_flag && num == 0 && conv.precision == 0)
		ft_strcpy(g_second_part, "");
	if (conv.precision_flag)
		append_nchar(g_first_part, '0', conv.precision
					- ft_strlen(g_second_part));
	if (conv.space_flag && !conv.plus_flag && num >= 0)
		prepend_nchar(g_first_part, ' ', 1);
	else if (conv.plus_flag && num >= 0)
		prepend_nchar(g_first_part, '+', 1);
	else if (num < 0)
		prepend_nchar(g_first_part, '-', 1);
	pad_for_field_width(conv);
	cat_and_free();
	return (ft_strlen(g_output));
}

/*
** convert_ou() - Convert an unsigned integer to a string in octal or decimal
** @args: The variadic arguments
** @conv: The conversion flags and parameters
**
** Note that when the precision_flag is set we take into account both
** @g_first_part and @g_second_part because @g_first_part may contain the
** alternate form leading zero. And this optional leading zero is not in
** @g_second_part because it's meant to be big enough to hold it. See
** allocate_globals() doc.
**
** Return: The number of resulting characters on success. -1 on error.
**         Sets g_output to the result string.
*/

int	convert_ou(va_list args, t_conv conv)
{
	char				*tmp;
	unsigned long long	num;

	num = get_num_ull(args, conv);
	if (!allocate_globals(conv, ft_num_digits_ull(num, get_base(conv))))
		return (-1);
	if (!(tmp = ft_ulltostr(
		num, conv.specifier == 'o' ? "01234567" : "0123456789")))
		return (free_globals());
	ft_strcpy(g_second_part, tmp);
	free(tmp);
	if (conv.precision_flag && num == 0 && conv.precision == 0)
		ft_strcpy(g_second_part, "");
	if (conv.specifier == 'o' && conv.hash_flag && g_second_part[0] != '0')
		append_nchar(g_first_part, '0', 1);
	if (conv.precision_flag)
		append_nchar(g_first_part, '0', conv.precision
					- ft_strlen(g_first_part) - ft_strlen(g_second_part));
	pad_for_field_width(conv);
	cat_and_free();
	return (ft_strlen(g_output));
}

/*
** convert_xx() - Convert an unsigned integer to a string in hexadecimal
** @args: The variadic arguments
** @conv: The conversion flags and parameters
**
** Return: The number of resulting characters on success. -1 on error.
**         Sets g_output to the result string.
*/

int	convert_xx(va_list args, t_conv conv)
{
	char				*tmp;
	unsigned long long	num;

	num = get_num_ull(args, conv);
	if (!allocate_globals(conv, ft_num_digits_ull(num, 16)))
		return (-1);
	if (!(tmp = ft_ulltostr(
		num, conv.specifier == 'x' ? "0123456789abcdef" : "0123456789ABCDEF")))
		return (free_globals());
	ft_strcpy(g_second_part, tmp);
	free(tmp);
	if (conv.precision_flag && num == 0 && conv.precision == 0)
		ft_strcpy(g_second_part, "");
	if (conv.hash_flag && num != 0)
		ft_strcpy(g_first_part, conv.specifier == 'x' ? "0x" : "0X");
	if (conv.precision_flag)
		append_nchar(g_first_part, '0', conv.precision
					- ft_strlen(g_second_part));
	pad_for_field_width(conv);
	cat_and_free();
	return (ft_strlen(g_output));
}
