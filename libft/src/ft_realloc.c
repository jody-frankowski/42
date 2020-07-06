/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
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
** ft_realloc - Reallocate some memory to a new size
** @ptr: Pointer to the memory to reallocate
** @old_size: Actual size of the allocated memory
** @new_size: Desired new size of the allocated memory
**
** If new_size is equal to 0 and ptr is not NULL this is equivalent to
** free(ptr). If ptr is NULL, and new_size is not 0 this is equivalent to
** malloc(new_size).
**
** Return: A pointer to the newly allocated memory on success. NULL on error or
** if new_size was zero.
*/

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new;

	if (new_size == 0)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	else
	{
		new = malloc(new_size);
		if (!new)
			return (NULL);
		if (ptr)
		{
			ft_memcpy(new, ptr, old_size);
			free(ptr);
		}
		return (new);
	}
}

/*
** ft_reallocf - Reallocate some memory to a new size
** @ptr: Pointer to the memory to reallocate
** @old_size: Actual size of the allocated memory
** @new_size: Desired new size of the allocated memory
**
** If new_size is equal to 0 and ptr is not NULL this is equivalent to
** free(ptr). If ptr is NULL, and new_size is not 0 this is equivalent to
** malloc(new_size).
** Contrary to ft_realloc, this function frees ptr even if malloc fails in order
** to avoid problems with coding style like so:
** ptr = ft_realloc(ptr, size, new_size);
**
** Return: A pointer to the newly allocated memory on success. NULL on error or
** if new_size was zero.
*/

void	*ft_reallocf(void *ptr, size_t old_size, size_t new_size)
{
	void *new;

	if (new_size == 0)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	else
	{
		new = malloc(new_size);
		if (!new)
		{
			free(ptr);
			return (NULL);
		}
		if (ptr)
		{
			ft_memcpy(new, ptr, old_size);
			free(ptr);
		}
		return (new);
	}
}
