/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

/*
** ft_count_words - Counts the number of words in s separated by chars in
** charset.
** @s: The string in which to count words
** @charset: The chars that delimit the words
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
