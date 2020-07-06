/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

/*
** ft_tab_push - Push a new element into a "tab"
** @tab: The "tab" to modify
** @data: The data to copy
** @width: The width of the "tab" elements
** @len: The number of elements in @tab before modification
**
** ft_tab_push is a low level function that is meant to be used by
** ft_array_push. Note that this function copies the content of @data. If you
** wish to store a pointer, use ft_tab_push_ptr.
**
** Return: 1 on success. 0 on errror.
*/

int		ft_tab_push(void **tab, void *data, size_t width, size_t len)
{
	void *new_tab;

	if (!tab)
		return (0);
	new_tab = ft_realloc(*tab, len * width, (len + 1) * width);
	if (!new_tab)
		return (0);
	ft_memmove(new_tab + len * width, data, width);
	*tab = new_tab;
	return (1);
}

/*
** ft_tab_push_ptr - Push a new pointer "tab"
** @tab: The "tab" to modify
** @ptr: The pointer to store
** @width: The width of the "tab" elements
** @len: The number of elements in @tab before modification
**
** ft_tab_push_ptr is a low level function that is meant to be used by
** ft_array_push_ptr. Note that this function copies the pointer @ptr. If
** you wish to store the content of @ptr, use ft_tab_push.
**
** Return: 1 on success. 0 on errror.
*/

int		ft_tab_push_ptr(void **tab, void *ptr, size_t width, size_t len)
{
	return (ft_tab_push(tab, &ptr, width, len));
}

/*
** ft_tab_free - Free a "tab"
** @tab: The "tab" to free
** @free_func: The freeing function to call on each elements
** @width: The width of the "tab" elements
** @len: The number of elements in @tab before modification
**
** The caller needs to make @free_func coherent with whether pointer or data was
** pushed into the tab.
**
** Return: NULL as a convenience for The Norm.
*/

void	*ft_tab_free(void *tab,
					void (*free_func)(void *),
					size_t width,
					size_t len)
{
	size_t i;

	if (free_func)
	{
		i = 0;
		while (i < len * width)
		{
			free_func(tab + i);
			i += width;
		}
	}
	free(tab);
	return (NULL);
}
