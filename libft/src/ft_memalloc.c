/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memalloc.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/07 16:25:21 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 16:25:21 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	*ft_memalloc(size_t size)
{
	void	*ptr;
	size_t	i;

	if (!(ptr = malloc(size)))
		return (NULL);
	i = 0;
	while (i < size)
		((char *)ptr)[i++] = 0;
	return (ptr);
}
