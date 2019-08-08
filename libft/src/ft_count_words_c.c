/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_count_words_c.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 10:24:40 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/08 10:24:40 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_count_words_c(char const *s, char c)
{
	char charset[2];

	charset[0] = c;
	charset[1] = '\0';
	return (ft_count_words(s, charset));
}
