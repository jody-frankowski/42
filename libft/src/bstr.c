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
** bstr_new() - Make a new bstr from a NULL-terminated string.
** @str: The pointer to char to use
**
** @str shouldn't be NULL and should point to a NULL-terminated string.
**
** Return: A bstr that points to @str.
*/

t_bstr	bstr_new(char *str)
{
	return ((t_bstr){str, ft_strlen(str)});
}
