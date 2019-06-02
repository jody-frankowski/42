/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_charcasecmp.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 16:54:05 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 16:54:05 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_charcasecmp(char c1, char c2)
{
	if (ft_isalpha(c1) && ft_isalpha(c2))
	{
		if ((c1 | 1 << 5) == (c2 | 1 << 5))
			return (0);
	}
	return ((unsigned char)c1 - (unsigned char)c2);
}
