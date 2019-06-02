/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split_whitespaces.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/11 22:25:26 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/11 22:25:26 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int		ft_count_words(char *str)
{
	int num;
	int in_word;

	num = 0;
	in_word = 0;
	while (*str)
	{
		if (ft_is_whitespace(*str) && in_word)
			num++;
		in_word = !ft_is_whitespace(*str);
		str++;
	}
	if (in_word)
		num++;
	return (num);
}

void	ft_strncpy(char *dest, char *src, int n)
{
	while (n > 1)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	*dest = '\0';
}

void	ft_malloc_and_copy(char **words, int i, char *str, char *begin_word)
{
	words[i] = (char *)malloc(sizeof(char) * ((str - begin_word) + 1));
	ft_strncpy(words[i], begin_word, (str - begin_word) + 1);
}

char	**ft_split_whitespaces(char *str)
{
	int		i;
	int		num_words;
	int		in_word;
	char	*begin_word;
	char	**words;

	num_words = ft_count_words(str);
	words = (char **)malloc(sizeof(*words) * (num_words + 1));
	in_word = 0;
	i = 0;
	while (*str)
	{
		if (!in_word && !ft_is_whitespace(*str))
			begin_word = str;
		if (ft_is_whitespace(*str) && in_word)
			ft_malloc_and_copy(words, i++, str, begin_word);
		in_word = !ft_is_whitespace(*str);
		str++;
	}
	if (in_word)
		ft_malloc_and_copy(words, i, str, begin_word);
	words[num_words] = NULL;
	return (words);
}
