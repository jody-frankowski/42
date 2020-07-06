/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stpncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_stpncpy(char *dst, const char *src, size_t len)
{
	char *save;

	while (*src && len)
	{
		*dst++ = *src++;
		len--;
	}
	save = dst;
	while (len)
	{
		*dst++ = '\0';
		len--;
	}
	return (save);
}
