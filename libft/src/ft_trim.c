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

char	*ft_ltrim(char *str, char *chars)
{
	while (*str && ft_incharset(*str, chars))
		str++;
	return (str);
}

char	*ft_rtrim(char *str, char *chars)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && ft_incharset(str[i], chars))
	{
		str[i] = '\0';
		i--;
	}
	return (str);
}

char	*ft_trim(char *str, char *chars)
{
	str = ft_ltrim(str, chars);
	str = ft_rtrim(str, chars);
	return (str);
}
