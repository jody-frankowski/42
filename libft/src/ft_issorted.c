/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_issorted.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/15 12:06:20 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 12:06:20 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>

int	ft_issorted(void *base, \
					size_t nel, \
					size_t width,
					int (*compar)(const void *, const void *))
{
	while (nel > 1)
	{
		if (compar(base, base + width) > 0)
			return (0);
		base += width;
		nel--;
	}
	return (1);
}
