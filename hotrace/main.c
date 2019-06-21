/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 18:19:58 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 18:19:58 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	put_data(uint64_t index, char *key, uint8_t length)
{
	t_tab	*old_next;
	t_tab	*new;
	char	*data;

	data = g_buf_ptr - length;
	if (g_tab[index].key == NULL)
	{
		g_tab[index].key = key;
		g_tab[index].data = data;
	}
	else
	{
		old_next = g_tab[index].next;
		new = malloc(sizeof(*new));
		new->next = old_next;
		new->key = key;
		new->data = data;
		g_tab[index].next = new;
	}
}

char	*search_key(char *key, uint8_t key_length, uint64_t index)
{
	t_tab *elem;

	if (g_tab[index].key && keycmp(key, g_tab[index].key, key_length) == 0)
	{
		return (g_tab[index].data);
	}
	elem = g_tab[index].next;
	while (elem)
	{
		if (keycmp(key, elem->key, key_length) == 0)
		{
			return (elem->data);
		}
		elem = elem->next;
	}
	return (NULL);
}

void	load_data(int is_reading_key, uint8_t length, uint32_t hash, char *key)
{
	while (1)
	{
		if (*g_buf_ptr == 0x0a)
		{
			*(g_buf_ptr - length - 1) = length | 0b10000000;
			if (!is_reading_key)
			{
				put_data(hash % TAB_LEN, key, length);
				hash = 5381;
			}
			else
				key = g_buf_ptr - length;
			is_reading_key = !is_reading_key;
			if (*(g_buf_ptr + 1) == 0x0a)
				break ;
			length = 0;
		}
		else
		{
			if (is_reading_key)
				hash = 33 * hash + *g_buf_ptr;
			length++;
		}
		g_buf_ptr++;
	}
}

void	search(void)
{
	uint8_t		length;
	uint32_t	hash;
	char		*data;

	hash = 5381;
	length = 0;
	g_buf_ptr += 2;
	while (g_buf_ptr != g_buf + 16 + g_buf_size)
	{
		if (*g_buf_ptr == 0x0a)
		{
			data = search_key(g_buf_ptr - length, length, hash % TAB_LEN);
			print_data(data, length);
			hash = 5381;
			length = -1;
		}
		else
		{
			hash = 33 * hash + *g_buf_ptr;
		}
		g_buf_ptr++;
		length++;
	}
	print_flush();
}

int		main(void)
{
	int		error;

	ft_read_all(0);
	error = treat_dict();
	if (error || error == -1)
	{
		free(g_buf);
		return (0);
	}
	if (cheat())
	{
		free(g_buf);
		return (0);
	}
	load_data(1, 0, 5381, NULL);
	search();
	free_tab();
	free(g_buf);
}
