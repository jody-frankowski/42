/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcspn.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/14 19:15:57 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/14 19:15:57 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strcspn(const char *s, const char *charset)
{
	size_t i;

	i = 0;
	while (s[i] && !ft_incharset(s[i], charset))
		i++;
	return (i);
}
