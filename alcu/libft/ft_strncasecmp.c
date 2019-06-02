/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncasecmp.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 17:39:54 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 17:39:54 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int	ft_strncasecmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while ((n - 1) && *s1 && ft_charcasecmp(*s1, *s2) == 0)
	{
		s1++;
		s2++;
		n--;
	}
	return (ft_charcasecmp(*s1, *s2));
}
