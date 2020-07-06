/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncasecmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int	ft_strncasecmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while ((n - 1) && *s1 && ft_charcasecmp(*s1, *s2) == 0)
	{
		s1++;
		s2++;
		n--;
	}
	return (ft_charcasecmp(*s1, *s2));
}
