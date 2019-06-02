/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split_whitespaces.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 09:01:12 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 09:01:12 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_is_whitespace(char c)
{
	return (c == '\n' || c == '\t' || c == ' ');
}

int		ft_count_words(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (str[i])
	{
		if (!ft_is_whitespace(str[i]))
			count++;
		i++;
	}
	while (str[i])
	{
		if (ft_is_whitespace(str[i - 1]) && !ft_is_whitespace(str[i]))
			count++;
		i++;
	}
	return (count);
}

char	*ft_strndup(char *src, int n)
{
	int		i;
	char	*copy;

	copy = (char *)malloc(sizeof(*copy) * (n + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < n)
	{
		copy[i] = *src;
		i++;
		src++;
	}
	copy[i] = '\0';
	return (copy);
}

char	**ft_split_whitespaces(char *str)
{
	int		num_words;
	char	*begin_word;
	char	**save;
	char	**words;

	num_words = ft_count_words(str);
	if (!(words = (char **)malloc(sizeof(*words) * (num_words + 1))))
		return (words);
	save = words;
	begin_word = NULL;
	while (*str)
	{
		if (!ft_is_whitespace(*str) && !begin_word && (begin_word = str))
		{
			while (*(str + 1) && !ft_is_whitespace(*(str + 1)))
				str++;
			if (!(*words = ft_strndup(begin_word, str - begin_word + 1)))
				return (NULL);
			words++;
			begin_word = NULL;
		}
		str++;
	}
	*words = NULL;
	return (save);
}
