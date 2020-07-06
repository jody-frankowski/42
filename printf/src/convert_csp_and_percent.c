/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_csp_and_percent.c                          :+:      :+:    :+:   */
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
** convert_c() - Convert a char argument to a string
** @args: The variadic arguments
** @conv: The conversion flags and parameters
**
** Return: The number of resulting characters on success. -1 on error.
**         Sets g_output to the result string.
*/

int	convert_c(va_list args, t_conv conv)
{
	unsigned char c;

	c = (unsigned char)va_arg(args, int);
	if (!(g_output = malloc(conv.field_width + 1)))
		return (-1);
	g_output[0] = '\0';
	if (conv.field_width > 1)
	{
		append_nchar(g_output, ' ', conv.field_width - 1);
		if (conv.minus_flag)
			prepend_nchar(g_output, c, 1);
		else
			append_nchar(g_output, c, 1);
	}
	else
		g_output[0] = c;
	if (conv.field_width > 1)
		return (conv.field_width);
	else
		return (1);
}

/*
** convert_s() - Convert a string argument to a string
** @args: The variadic arguments
** @conv: The conversion flags and parameters
**
** Return: The number of resulting characters on success. -1 on error.
**         Sets g_output to the result string.
*/

int	convert_s(va_list args, t_conv conv)
{
	char *str;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	if (!allocate_globals(conv, ft_strlen(str)))
		return (-1);
	if (conv.precision_flag)
		ft_strlcpy(g_second_part, str, conv.precision + 1);
	else
		ft_strcpy(g_second_part, str);
	pad_for_field_width(conv);
	cat_and_free();
	return (ft_strlen(g_output));
}

/*
** convert_p() - Convert a pointer argument to a string
** @args: The variadic arguments
** @conv: The conversion flags and parameters
**
** We don't call convert_xx because the behavior is slighly different:
** %p with NULL gives "0x0" on macOS and "(nil)" on Linux.
**
** Return: The number of resulting characters on success. -1 on error.
**         Sets g_output to the result string.
*/

int	convert_p(va_list args, t_conv conv)
{
	char				*tmp;
	unsigned long long	num;

	conv.length_modifier_flag = 1;
	conv.length_modifier = L;
	num = get_num_ull(args, conv);
	if (!allocate_globals(conv, ft_num_digits_ull(num, 16)))
		return (-1);
	if (!(tmp = ft_ulltostr(num, "0123456789abcdef")))
		return (free_globals());
	ft_strcpy(g_second_part, tmp);
	free(tmp);
	ft_strcpy(g_first_part, "0x");
	pad_for_field_width(conv);
	cat_and_free();
	return (ft_strlen(g_output));
}

/*
** convert_percent() - Make a string with a percent sign
** @args: The variadic arguments
** @conv: The conversion flags and parameters
**
** Return: The number of resulting characters on success. -1 on error.
**         Sets g_output to the result string.
*/

int	convert_percent(va_list args, t_conv conv)
{
	(void)args;
	if (!allocate_globals(conv, 1))
		return (-1);
	ft_strcpy(g_second_part, "%");
	pad_for_field_width(conv);
	cat_and_free();
	return (ft_strlen(g_output));
}
