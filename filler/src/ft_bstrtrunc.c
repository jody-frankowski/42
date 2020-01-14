/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_bstrtrunc.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/08 17:34:43 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/08 17:34:43 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
