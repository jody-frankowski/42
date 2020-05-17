/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

/*
** ft_ltrim() - Remove leading characters from a string
** @str:     The string to use
** @charset: The characters to remove
**
** ft_ltrim() will "remove" leading characters by returning a pointer to the
** first character that isn't in @charset.
**
** Return: A pointer in @str after the leading characters.
*/

char	*ft_ltrim(char *str, char *charset)
{
	while (*str && ft_incharset(*str, charset))
		str++;
	return (str);
}

/*
** ft_rtrim() - Remove trailing characters from a string
** @str:     The string to use
** @charset: The characters to remove
**
** ft_rtrim() will "remove" trailing characters by overwriting them with \0
** characters.
**
** Return: A pointer to @str.
*/

char	*ft_rtrim(char *str, char *charset)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && ft_incharset(str[i], charset))
	{
		str[i] = '\0';
		i--;
	}
	return (str);
}

/*
** ft_trim() - Remove leading and trailing characters from a string
** @str:     The string to use
** @charset: The characters to remove
**
** ft_trim() will "remove" leading and trailing characters by calling ft_ltrim()
** and ft_rtrim() on @str.
**
** Return: A pointer in @str after the leading characters and with the trailing
** characters overwritten with \0 characters.
*/

char	*ft_trim(char *str, char *charset)
{
	str = ft_ltrim(str, charset);
	str = ft_rtrim(str, charset);
	return (str);
}
