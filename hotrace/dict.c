/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dict.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 18:19:58 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 18:19:58 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*is_dict(void)
{
	char	*g_buf_ptr;
	int		i;

	g_buf_ptr = g_buf;
	while (1)
	{
		if (g_buf_ptr[0] == 0x0a)
			break ;
		i = 0;
		while (i < 5)
		{
			if (!(g_buf_ptr[i] - 65 <= 25))
				return (0);
			i++;
		}
		if (g_buf_ptr[i] != 0x0a)
			return (0);
		g_buf_ptr += 12;
	}
	return (g_buf_ptr);
}

char	*load_dict(char **dict, char *g_buf_ptr)
{
	int	i;
	int	is_key;
	int	key;

	g_buf_ptr = g_buf;
	is_key = 1;
	while (*g_buf_ptr != 0x0a)
	{
		if (is_key)
		{
			i = 0;
			key = 0;
			while (i < 5)
			{
				key |= (g_buf_ptr[i] & 0b00011111) << 5 * i;
				i++;
			}
		}
		else
			dict[key] = g_buf_ptr;
		is_key = !is_key;
		g_buf_ptr += 6;
	}
	return (g_buf_ptr);
}

void	search_dict(char **dict, char *g_buf_ptr)
{
	int	i;
	int	key;

	while (g_buf_ptr < g_buf + g_buf_size)
	{
		i = 0;
		key = 0;
		while (i < 5)
		{
			key |= (g_buf_ptr[i] & 0b00011111) << 5 * i;
			i++;
		}
		print(dict[key], 6);
		g_buf_ptr += 6;
	}
	print_flush();
}

int		treat_dict(void)
{
	char	*g_buf_ptr;
	char	**dict;

	if (!(g_buf_ptr = is_dict()))
		return (0);
	if (!(dict = malloc(33554432 * sizeof(*dict))))
		return (-1);
	g_buf_ptr = load_dict(dict, g_buf_ptr);
	g_buf_ptr++;
	search_dict(dict, g_buf_ptr);
	free(dict);
	return (1);
}
