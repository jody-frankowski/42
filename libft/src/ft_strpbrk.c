/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strpbrk.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 18:07:28 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 18:07:28 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>

char	*ft_strpbrk(const char *s, const char *charset)
{
	char *save;

	while (*s)
	{
		save = (char *)charset;
		while (*charset)
		{
			if (*s == *charset)
				return ((char *)s);
			charset++;
		}
		charset = save;
		s++;
	}
	return (NULL);
}
