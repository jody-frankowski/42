/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_realloc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 12:09:18 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 20:50:26 by tiperoul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** Does not support size == 0
*/

void	*ft_realloc(void *ptr, size_t size)
{
	void *new;

	if (size == 0)
		return (NULL);
	new = malloc(size);
	if (!new)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new, ptr);
		free(ptr);
	}
	else
		*(char *)new = '\0';
	return (new);
}
