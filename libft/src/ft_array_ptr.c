/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_array_push_ptr - Push a new pointer into a t_array
** @array: The t_array to modify
** @ptr: The pointer to store
**
** Note that this function copies the pointer @ptr. If you wish to store the
** content of @ptr, use ft_array_push.
**
** Return: 1 on success. 0 on errror.
*/

int		ft_array_push_ptr(t_array *array, void *ptr)
{
	return (ft_array_push(array, &ptr));
}

/*
** ft_array_get_ptr - Get a pointer from a t_array
** @array: The t_array to query
** @index: The index of the element
**
** Return: The pointer that was stored at @index
**
** /!\ No check is done to make sure that @index is within the limits of the
** array.
*/

void	*ft_array_get_ptr(t_array *array, size_t index)
{
	void **tmp;

	tmp = ft_array_get(array, index);
	return (*tmp);
}
