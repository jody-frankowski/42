/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
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

int	ft_sprintf(char *str, const char *format, ...)
{
	va_list	args;
	int		len;

	va_start(args, format);
	len = ft_vsprintf(str, format, args);
	va_end(args);
	return (len);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	int		i;
	va_list	args;

	va_start(args, format);
	i = ft_vdprintf(fd, format, args);
	va_end(args);
	return (i);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	args;

	va_start(args, format);
	i = ft_vprintf(format, args);
	va_end(args);
	return (i);
}
