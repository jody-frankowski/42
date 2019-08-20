/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrev.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 17:21:17 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 17:21:17 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

/*
** ft_strrev - Reverses a string
** @s: The string to reverse
**
** Return: The string reversed
*/

char	*ft_strrev(char const * const s)
{
	size_t	len;
	size_t	i;
	char	*rev;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (!(rev = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		rev[i] = s[len - i - 1];
		i++;
	}
	return (rev);
}
