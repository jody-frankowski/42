/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstrtrunc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** ft_bstrtrunc - Truncate a binary string
** @src: A pointer to pointer to the string to truncate
** @start: The start offset for the truncation
** @len: The length of the truncation
**
** ft_bstrtrunc will truncate a binary string based on the start and len
** argument.
** The function will always null terminate the copied string.
** The function will free the string src on success for the caller.
**
** Return: 1 on success. 0 on failure.
*/

int	ft_bstrtrunc(void **src, size_t start, size_t len)
{
	void *trunc;

	if (!src || !*src)
		return (0);
	trunc = ft_bstrdup(*src + start, len);
	if (!trunc)
		return (0);
	free(*src);
	*src = trunc;
	return (1);
}
