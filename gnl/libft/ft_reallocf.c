/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_reallocf.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/20 19:24:43 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/20 19:24:43 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

/*
** Returns a pointer to a new allocated memory of new_size that contains
** the memory pointed by ptr of old_size, or NULL on error.
** If ptr is NULL this is equivalent to malloc(new_size).
** If malloc fails the function will free ptr for the caller.
*/

void	*ft_reallocf(void *ptr, size_t old_size, size_t new_size)
{
	void *new;

	if (!(new = malloc(new_size)))
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (new);
	ft_memcpy(new, ptr, old_size);
	free(ptr);
	return (new);
}
