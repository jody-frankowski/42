/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diouxx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libprintf.h"

/*
** get_base() - Get the target base of a conversion based on its specifier
** @conv: The t_conv to use
**
** Return: The target base.
*/

int					get_base(t_conv conv)
{
	if (conv.specifier == 'o')
		return (8);
	else if (conv.specifier == 'd' ||
			conv.specifier == 'i' ||
			conv.specifier == 'u')
		return (10);
	else
		return (16);
}

long long			get_num_ll(va_list args, t_conv conv)
{
	if (conv.length_modifier_flag)
	{
		if (conv.length_modifier == HH)
			return ((char)va_arg(args, int));
		else if (conv.length_modifier == H)
			return ((short)va_arg(args, int));
		else if (conv.length_modifier == L)
			return ((long)va_arg(args, long));
		else
			return ((long long)va_arg(args, long long));
	}
	else
		return ((int)va_arg(args, int));
}

unsigned long long	get_num_ull(va_list args, t_conv conv)
{
	if (conv.length_modifier_flag)
	{
		if (conv.length_modifier == HH)
			return ((unsigned char)va_arg(args, unsigned int));
		else if (conv.length_modifier == H)
			return ((unsigned short)va_arg(args, unsigned int));
		else if (conv.length_modifier == L)
			return ((unsigned long)va_arg(args, unsigned long));
		else
			return ((unsigned long long)va_arg(args, unsigned long long));
	}
	else
		return ((unsigned int)va_arg(args, unsigned int));
}
