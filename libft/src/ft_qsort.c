/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
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

static void	*hoare_partition(void *base, \
					size_t nel, \
					size_t width,
					int (*compar)(const void *, const void *))
{
	void *pivot;
	void *start;
	void *end;

	if (!(pivot = malloc(width)))
		return (NULL);
	ft_memcpy(pivot, base, width);
	start = base - width;
	end = base + ((nel - 1) * width) + width;
	while (1)
	{
		start += width;
		while (compar(start, pivot) < 0)
			start += width;
		end -= width;
		while (compar(end, pivot) > 0)
			end -= width;
		if (start >= end)
		{
			free(pivot);
			return (end);
		}
		ft_swap(start, end, width);
	}
}

void		ft_qsort(void *base, \
				size_t nel, \
				size_t width,
				int (*compar)(const void *, const void *))
{
	size_t	num_low;
	size_t	num_high;
	void	*partition;
	void	*base_low;
	void	*base_high;

	if (nel <= 1)
		return ;
	partition = hoare_partition(base, nel, width, compar);
	base_low = base;
	base_high = partition + width;
	num_low = (partition - base + 1) / width;
	num_high = ((base + (nel * width)) - base_high) / width;
	ft_qsort(base_low, num_low, width, compar);
	ft_qsort(base_high, num_high, width, compar);
}
