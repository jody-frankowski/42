/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	unsigned int begin;
	unsigned int end;

	if (!s)
		return (NULL);
	if (!*s)
		return (ft_strnew(0));
	begin = 0;
	while (s[begin] && (s[begin] == ' ' || s[begin] == '\n' || \
						s[begin] == '\t'))
		begin++;
	end = ft_strlen(s) - 1;
	while (s + end != s && (s[end] == ' ' || s[end] == '\n' || s[end] == '\t'))
		end--;
	if (end < begin)
		return (ft_strnew(0));
	return (ft_strsub(s, begin, end - begin + 1));
}
