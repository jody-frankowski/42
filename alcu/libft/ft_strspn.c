/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strspn.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/14 19:14:37 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/14 19:14:37 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strspn(const char *s, const char *charset)
{
	size_t i;

	i = 0;
	while (s[i] && ft_incharset(s[i], charset))
		i++;
	return (i);
}
