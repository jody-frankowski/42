/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_range.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/11 18:51:24 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/11 18:51:25 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int *ints;
	int i;

	if (min >= max)
		return (NULL);
	ints = (int *)malloc((sizeof(*ints)) * (max - min));
	if (!ints)
		return (ints);
	i = 0;
	while (min < max)
	{
		ints[i] = min;
		min++;
		i++;
	}
	return (ints);
}
