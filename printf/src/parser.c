/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libprintf.h"

void	set_length_modifier(const char **format, t_conv *conv)
{
	if (ft_strncmp(*format, "hh", 2) == 0)
	{
		conv->length_modifier_flag = 1;
		conv->length_modifier = HH;
		(*format) += 2;
	}
	else if (ft_strncmp(*format, "ll", 2) == 0)
	{
		conv->length_modifier_flag = 1;
		conv->length_modifier = LL;
		(*format) += 2;
	}
	else if (ft_strncmp(*format, "h", 1) == 0)
	{
		conv->length_modifier_flag = 1;
		conv->length_modifier = H;
		(*format)++;
	}
	else if (ft_strncmp(*format, "l", 1) == 0)
	{
		conv->length_modifier_flag = 1;
		conv->length_modifier = L;
		(*format)++;
	}
}

void	set_float_length_modifier(const char **format, t_conv *conv)
{
	if (ft_strncmp(*format, "L", 1) == 0)
	{
		conv->length_modifier_flag = 1;
		conv->length_modifier = LF;
		(*format)++;
	}
}

void	set_flag(char c, t_conv *conv)
{
	if (c == '#')
		conv->hash_flag = 1;
	if (c == '0')
		conv->zero_flag = 1;
	if (c == '-')
		conv->minus_flag = 1;
	if (c == ' ')
		conv->space_flag = 1;
	if (c == '+')
		conv->plus_flag = 1;
}

/*
** parse_conversion() - Parse the flags and conversion specifier into a t_conv
** @format: A pointer to the pointer to the format string
**
** At the end @format will point to the character just after the conversion
** specifier character.
**
** Negative precision behavior:
** https://stackoverflow.com/a/44639592
** printf.c:
** #include <stdio.h>
**
** int main()
** {
**     printf("|%.-1s|\n", "123 abc");
**     printf("|%.-1d|\n", 333);
** }
**
** Linux's glibc:
** |%.0-1s|
** |%.0-1d|
**
** MacOs' libc:
** | |
** |333|
**
** Return: A t_conv.
*/

t_conv	parse_conversion(const char **format)
{
	t_conv	conv;

	ft_memset(&conv, 0, sizeof(conv));
	while (ft_incharset(**format, "#0- +"))
	{
		set_flag(**format, &conv);
		(*format)++;
	}
	if (**format >= '1' && **format <= '9')
		conv.field_width = ft_strtol(*format, (char **)format, 10);
	if (**format == '.')
	{
		(*format)++;
		conv.precision = ft_strtol(*format, (char**)format, 10);
		conv.precision_flag = conv.precision < 0 ? 0 : 1;
	}
	set_length_modifier(format, &conv);
	set_float_length_modifier(format, &conv);
	conv.specifier = **format;
	(*format)++;
	return (conv);
}
