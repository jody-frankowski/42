/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "libprintf.h"

char	*g_first_part;
char	*g_second_part;
char	*g_output;
int		(*g_converter['x' + 1])(va_list args, t_conv conv);

/*
** allocate_globals() - Allocate the global buffers
** @conv: The t_conv to use
** @num_chars: The number of chars that the converted value takes
**
** The buffers are allocated based on the field width, the precision and
** @num_chars. This functions can be used by the d, i, o, u, p, x, X, f and F
** specifiers.
**
** @g_first_part is meant to hold number symbols ('-', '+', ' ', '0' and '0x'),
** the precision padding, and optionally the left padding from the field width.
** @g_second_part is meant to hold the converted
** number or string, and the right padding from the field width.
** @g_output is meant to contain the concatenation of @g_first_part and
** @g_second_part. This should be the result of a convert_ function.
**
** Return: 1 on success. 0 on error.
*/

int		allocate_globals(t_conv conv, int num_chars)
{
	g_first_part = malloc(biggest(conv.field_width, conv.precision, 0) + 2 + 1);
	if (!g_first_part)
		return (0);
	g_second_part = malloc(biggest(conv.field_width, num_chars, 0) + 1);
	if (!g_second_part)
	{
		free(g_first_part);
		return (0);
	}
	g_output = malloc(biggest(conv.field_width, conv.precision, num_chars)
					+ 2 + 1);
	if (!g_output)
	{
		free(g_second_part);
		free(g_first_part);
		return (0);
	}
	g_second_part[0] = '\0';
	g_first_part[0] = '\0';
	g_output[0] = '\0';
	return (1);
}

void	cat_and_free(void)
{
	ft_strcat(g_output, g_first_part);
	ft_strcat(g_output, g_second_part);
	free(g_first_part);
	free(g_second_part);
}

int		free_globals(void)
{
	free(g_first_part);
	free(g_second_part);
	free(g_output);
	g_first_part = NULL;
	g_second_part = NULL;
	g_output = NULL;
	return (-1);
}
