/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bstr_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** bstr_read_until() - Read chars from a bstr until a chaset
** @str:     A pointer to the bstr
** @charset: The charset which stops the reading
**
** bstr_read_until() will advance the str pointer in a bstr by "reading" chars
** from a charset until the first character that is in @charset or the end of
** @str.
**
** Return: The bstr that was read.
*/

t_bstr	bstr_read_until(t_bstr *str, char *charset)
{
	char	*old;
	size_t	i;

	i = 0;
	while (i < str->len && !ft_incharset(str->str[i], charset))
		i++;
	old = str->str;
	str->str += i;
	str->len -= i;
	return ((t_bstr){old, i});
}
