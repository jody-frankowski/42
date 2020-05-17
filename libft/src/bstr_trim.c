/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bstr_trim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** bstr_ltrim() - Remove leading characters from a bstr
** @str:     The bstr to use
** @charset: The characters to remove
**
** Return: A new bstr without the leading characters.
*/

t_bstr	bstr_ltrim(t_bstr str, char *charset)
{
	size_t	i;

	i = 0;
	while (i < str.len && ft_incharset(str.str[i], charset))
		i++;
	return ((t_bstr){str.str + i, str.len - i});
}

/*
** bstr_rtrim() - Remove trailing characters from a bstr
** @str:     The bstr to use
** @charset: The characters to remove
**
** Return: A new bstr without the trailing characters.
*/

t_bstr	bstr_rtrim(t_bstr str, char *charset)
{
	int	i;

	i = str.len - 1;
	while (i >= 0 && ft_incharset(str.str[i], charset))
		i--;
	return ((t_bstr){str.str, i + 1});
}

/*
** bstr_trim() - Remove leading and trailing characters from a bstr
** @str:     The bstr to use
** @charset: The characters to remove
**
** Return: A new bstr without the leading and trailing characters.
*/

t_bstr	bstr_trim(t_bstr str, char *charset)
{
	str = bstr_ltrim(str, charset);
	str = bstr_rtrim(str, charset);
	return (str);
}
