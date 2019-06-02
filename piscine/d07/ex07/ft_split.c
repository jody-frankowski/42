/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_split.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/12 21:01:25 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 21:01:26 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

int		f(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

int		ft_count_words(char *str, char *charset)
{
	int count;
	int i;

	count = 0;
	i = 0;
	if (str[i])
	{
		if (!f(str[i], charset))
			count++;
		i++;
	}
	while (str[i])
	{
		if (f(str[i - 1], charset) &&
			!f(str[i], charset))
			count++;
		i++;
	}
	return (count);
}

char	*ft_strndup(char *src, int n)
{
	int		i;
	int		len;
	char	*copy;

	len = 0;
	while (src[len] && len < n)
		len++;
	copy = (char *)malloc(sizeof(*copy) * (len + 1));
	if (!copy)
		return (copy);
	i = 0;
	while (src[i] && i < n)
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	**ft_split(char *str, char *charset)
{
	int		num_words;
	int		i;
	char	*begin_word;
	char	**words;

	num_words = ft_count_words(str, charset);
	if (!(words = (char **)malloc(sizeof(*words) * (num_words + 1))))
		return (NULL);
	begin_word = NULL;
	i = 0;
	while (str[i])
	{
		if (!f(str[i], charset) && !begin_word && (begin_word = str + i))
		{
			while (str[i] && !f(str[i], charset))
				i++;
			(*words) = ft_strndup(begin_word, (str + i) - begin_word);
			words++;
			begin_word = NULL;
		}
		if (!str[i++])
			break ;
	}
	*words = NULL;
	return (words - num_words);
}
