/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bstr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** str_to_bstr() - Make a new bstr from a NULL-terminated string.
** @str: The pointer to char to use
**
** @str shouldn't be NULL and should point to a NULL-terminated string.
**
** Return: A bstr that points to @str.
*/

t_bstr	str_to_bstr(char *str)
{
	return ((t_bstr){str, ft_strlen(str)});
}

/*
** bstr_cmp() - Compare two bstr
** @s1: The first bstr to compare
** @s2: The second bstr to compare
**
** Return:
*/

int		bstr_cmp(t_bstr *s1, t_bstr *s2)
{
	size_t	i;

	i = 0;
	while (i < s1->len && i < s2->len)
	{
		if (s1->str[i] != s2->str[i])
			return (s1->str[i] - s2->str[i]);
		i++;
	}
	return (s1->len - s2->len);
}
