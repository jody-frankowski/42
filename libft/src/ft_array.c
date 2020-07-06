/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** ft_array_new - Create a new t_array
** @width: The width of the elements
** @free_func: The function used to free the individual elements
**
** Return: The new t_array on succes. NULL on error.
*/

t_array	*ft_array_new(size_t width, void (*free_func)(void *))
{
	t_array *array;

	array = malloc(sizeof(*array));
	if (!array)
		return (NULL);
	array->bytes = NULL;
	array->len = 0;
	array->width = width;
	array->free = free_func;
	return (array);
}

/*
** ft_array_to_null_terminated - Convert a t_array to a null-terminated "tab"
** @array: t_array to convert
**
** ft_array_to_null_terminated will convert a t_array to a null-terminated "tab"
** by pushing a last NULL pointer and freeing the structure t_array, returning
** only the pointer to the "tab".
**
** Return: The converted tab on success, NULL on error. On error the array is
** freed.
*/

void	*ft_array_to_null_terminated(t_array *array)
{
	void *output;

	if (!ft_array_push(array, (void *[]){NULL}))
		return (ft_array_free(array));
	output = array->bytes;
	free(array);
	return (output);
}

/*
** ft_array_push - Push a new element into a t_array
** @array: The t_array to modify
** @data: The data to copy
**
** Note that this function copies the content of @data. If you wish to store a
** pointer, use ft_array_push_ptr.
**
** Return: 1 on success. 0 on errror.
*/

int		ft_array_push(t_array *array, void *data)
{
	int success;

	if (!array)
		return (0);
	success = ft_tab_push((void **)&(array->bytes),
						data,
						array->width,
						array->len);
	if (success)
		array->len++;
	return (success);
}

/*
** ft_array_get - Get an element from a t_array
** @array: The t_array to query
** @index: The index of the element
**
** Return: A pointer to the element at @index
**
** /!\ No check is done to make sure that @index is within the limits of the
** array.
*/

void	*ft_array_get(t_array *array, size_t index)
{
	return (array->bytes + index * array->width);
}

/*
** ft_array_free - Free a t_array
** @array: The t_array to free
**
** Return: NULL as a convenience for The Norm.
*/

void	*ft_array_free(t_array *array)
{
	ft_tab_free(array->bytes, array->free, array->width, array->len);
	free(array);
	return (NULL);
}
