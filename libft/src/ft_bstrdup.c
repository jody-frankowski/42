/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstrdup.c                                       :+:      :+:    :+:   */
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
** ft_bstrdup - Copies a binary string
** @src: The source binary string
** @len: How many chars to copy
**
** ft_bstrdup will malloc and copy the binary string src up to len bytes.
** src does not need to be null terminated, and can also contain null bytes.
** The function will always null terminate the copied string.
**
** Return: A pointer to the copy on success. NULL on error.
*/

void	*ft_bstrdup(void *src, size_t len)
{
	void *copy;

	if (!src)
		return (NULL);
	copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	ft_memcpy(copy, src, len);
	((unsigned char *)copy)[len] = '\0';
	return (copy);
}
