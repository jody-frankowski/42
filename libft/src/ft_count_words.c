/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_count_words.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/07 19:57:12 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 19:57:12 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

/*
** Returns the number of words in s separated by chars in charset.
** If
*/

size_t	ft_count_words(char const *s, char const *charset)
{
	size_t	words;
	int		inword;

	if (!s)
		return (0);
	words = 0;
	inword = 0;
	while (*s)
	{
		if (!ft_incharset(*s, charset) && !inword)
		{
			inword = 1;
			words++;
		}
		if (ft_incharset(*s, charset))
			inword = 0;
		s++;
	}
	return (words);
}
