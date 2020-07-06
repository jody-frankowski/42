/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libprintf.h"

int		biggest(int a, int b, int c)
{
	if (a >= b && a >= c)
		return (a);
	else if (b >= a && b >= c)
		return (b);
	else
		return (c);
}

void	pad_for_field_width(t_conv conv)
{
	if (conv.field_width > 0)
	{
		if (conv.zero_flag && !conv.minus_flag && !conv.precision)
			append_nchar(g_first_part, '0', conv.field_width
						- ft_strlen(g_first_part) - ft_strlen(g_second_part));
		else if (conv.minus_flag)
			append_nchar(g_second_part, ' ', conv.field_width
						- ft_strlen(g_first_part) - ft_strlen(g_second_part));
		else
			prepend_nchar(g_first_part, ' ', conv.field_width
						- ft_strlen(g_first_part) - ft_strlen(g_second_part));
	}
}

void	append_nchar(char *str, char c, int n)
{
	if (n <= 0)
		return ;
	while (*str)
		str++;
	while (n--)
		*str++ = c;
	*str = '\0';
}

void	prepend_nchar(char *str, char c, int n)
{
	char	prev;
	char	tmp;
	int		i;

	if (n <= 0)
		return ;
	while (n--)
	{
		i = 0;
		prev = str[i];
		str[i] = c;
		i++;
		while (prev)
		{
			tmp = str[i];
			str[i] = prev;
			prev = tmp;
			i++;
		}
		str[i] = prev;
	}
}

void	init_converter(void)
{
	g_converter['d'] = convert_di;
	g_converter['i'] = convert_di;
	g_converter['f'] = convert_ff;
	g_converter['F'] = convert_ff;
	g_converter['o'] = convert_ou;
	g_converter['u'] = convert_ou;
	g_converter['x'] = convert_xx;
	g_converter['X'] = convert_xx;
	g_converter['c'] = convert_c;
	g_converter['s'] = convert_s;
	g_converter['p'] = convert_p;
	g_converter['%'] = convert_percent;
}
