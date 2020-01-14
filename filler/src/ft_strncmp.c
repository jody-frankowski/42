/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strncmp.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 15:16:43 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 15:16:43 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while ((n - 1) && *s1 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	return (*(unsigned char*)s1 - *(unsigned char*)s2);
}
