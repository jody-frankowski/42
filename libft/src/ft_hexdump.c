/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_hexdump.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/08 16:55:34 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/08 16:55:34 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include "libft.h"

/*
** ft_hexdump - Print a basic hexdump
** @ptr: Pointer to the memory to print
** @len: How much bytes to print
**
** Return: On success 0. On error -1, and errno shall be set to indicate the
** error.
*/

void	ft_hexdump(const void *ptr, size_t len)
{
	size_t			i;
	size_t			j;
	const t_byte	*mem = ptr;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < HEXDUMP_WIDTH && i + j < len)
		{
			printf("%02hhx ", mem[i + j]);
			j++;
		}
		j = 0;
		while (j < HEXDUMP_WIDTH && i + j < len)
		{
			if (isprint(mem[i + j]))
				printf("%c", mem[i + j]);
			else
				printf(".");
			j++;
		}
		printf("\n");
		i += HEXDUMP_WIDTH;
	}
}
