/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bstr_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

/*
** bstr_array_is_in() - Check if a bstr is in an array
** @array: The array search in
** @str:   The bstr to search
**
** Return: true if @str is found, else false.
*/

bool	bstr_array_is_in(t_array *bstr_array, t_bstr str)
{
	size_t	i;
	t_bstr	*element;

	i = 0;
	while (i < bstr_array->len)
	{
		element = ft_array_get(bstr_array, i);
		if (bstr_cmp(str, *element) == 0)
			return (true);
		i++;
	}
	return (false);
}

/*
** bstr_array_add() - Add a bstr to an array
** @array: The array to add to
** @str:   The bstr to add
**
** Return: On success true, false on malloc error.
*/

bool	bstr_array_add(t_array *bstr_array, t_bstr str)
{
	if (bstr_array_is_in(bstr_array, str))
		return (true);
	if (!ft_array_push(bstr_array, &str))
		return (false);
	return (true);
}

/*
** bstr_array_free() - Free bstr arrays
** @a: The first array to free
** @b: The second array to free
**
** Return: false as a convenience for The Norm.
*/

bool	bstr_array_free(t_array *array1, t_array *array2)
{
	if (array1)
		ft_array_free(array1);
	if (array2)
		ft_array_free(array2);
	return (false);
}
