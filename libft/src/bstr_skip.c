/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bstr_skip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** bstr_skip_char() - Skip a char in a bstr
** @str: A pointer to the bstr
** @c:   The char to skip
**
** bstr_skip_char() will advance the str pointer in a bstr by skipping a single
** char. This function will always make sure that the bstr is still long enough
** for a char to be skipped.
**
** Return: 1 if a char was skipped, else 0.
*/

size_t	bstr_skip_char(t_bstr *str, char c)
{
	if (str->len >= 1 && str->str[0] == c)
	{
		str->str++;
		str->len--;
		return (1);
	}
	else
		return (0);
}

/*
** bstr_skip_chars() - Skip chars in a bstr
** @str:     A pointer to the bstr
** @charset: The charset to skip
**
** bstr_skip_chars() will advance the str pointer in a bstr by skipping chars
** from a charset until the first character that isn't in @charset or the end of
** @str.
**
** Return: The number of characters that were skipped.
*/

size_t	bstr_skip_chars(t_bstr *str, char *charset)
{
	size_t	i;

	i = 0;
	while (i < str->len && ft_incharset(str->str[i], charset))
		i++;
	str->str += i;
	str->len -= i;
	return (i);
}
