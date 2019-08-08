/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/07 18:06:29 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 18:06:29 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
