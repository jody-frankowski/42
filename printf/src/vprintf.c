/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vprintf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "libprintf.h"

int	ft_vdprintf(int fd, const char *format, va_list args)
{
	int		i;
	int		len;
	t_conv	conv;

	init_converter();
	i = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			conv = parse_conversion(&format);
			if ((len = g_converter[conv.specifier](args, conv)) == -1)
				return (-1);
			write(fd, g_output, len);
			i += len;
			free(g_output);
		}
		else
		{
			ft_putchar_fd(fd, *format++);
			i++;
		}
	}
	return (i);
}

int	ft_vsprintf(char *str, const char *format, va_list args)
{
	int		i;
	int		len;
	t_conv	conv;

	init_converter();
	i = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			conv = parse_conversion(&format);
			if ((len = g_converter[conv.specifier](args, conv)) == -1)
				return (-1);
			ft_memmove(str + i, g_output, len);
			i += len;
			free(g_output);
		}
		else
			str[i++] = *format++;
	}
	str[i] = '\0';
	return (i);
}

int	ft_vprintf(const char *format, va_list args)
{
	return (ft_vdprintf(1, format, args));
}
