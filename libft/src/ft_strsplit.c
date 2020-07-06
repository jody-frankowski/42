/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	t_array	*words;
	char	*begin_word;
	char	*word_copy;

	if (!s)
		return (NULL);
	if (!(words = ft_array_new(sizeof(char *), NULL)))
		return (NULL);
	begin_word = NULL;
	while (*s)
	{
		if (*s != c && !begin_word)
			begin_word = (char*)s;
		if ((*(s + 1) == c || !*(s + 1)) && begin_word)
		{
			if (!(word_copy = ft_strndup(begin_word, s - begin_word + 1)))
				return (ft_array_free(words));
			if (!ft_array_push(words, &word_copy))
				return (ft_array_free(words));
			begin_word = NULL;
		}
		s++;
	}
	return ((char **)ft_array_to_null_terminated(words));
}
