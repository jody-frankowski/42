/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_map.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 11:05:29 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 11:05:30 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_map(int *tab, int length, int (*f)(int))
{
	int *returns;
	int *save;

	if (!f || !tab)
		return (NULL);
	returns = (int *)malloc(sizeof(f(0)) * length);
	if (!returns)
		return (NULL);
	save = returns;
	while (length-- > 0)
		*returns++ = f(*tab++);
	return (save);
}
