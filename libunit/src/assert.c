/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   assert.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/11 19:54:56 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/11 19:54:56 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

int assert_mem_eq(
					 const char *a_tok,
					 const char *b_tok,
					 const char *func,
					 const char *file,
					 size_t line,
					 const void *a,
					 const void *b,
					 size_t len
				  )
{
	if (memcmp(a, b, len) != 0)
	{
		fprintf(stderr,
				"%s: mem@%s != mem@%s (%s:%lu)\n",
				func, a_tok, b_tok, file, line);
		fprintf(stderr, "%s:\n", a_tok);
		ft_hexdump(a, len);
		printf("\n");
		fprintf(stderr, "%s:\n", b_tok);
		ft_hexdump(b, len);
		printf("\n");
		return (0);
	}
	return (1);
}

int assert_ptr_eq(
					 const char *a_tok,
					 const char *b_tok,
					 const char *func,
					 const char *file,
					 size_t line,
					 const void *a,
					 const void *b
					 )
{
	if (a != b)
	{
		fprintf(stderr,
				"%s: %s != %s (%p != %p) (%s:%lu)\n",
				func, a_tok, b_tok, a, b, file, line);
		return (0);
	}
	return (1);
}

int assert_str_eq(
					 const char *a_tok,
					 const char *b_tok,
					 const char *func,
					 const char *file,
					 size_t line,
					 const char *a,
					 const char *b
					 )
{
	if (strcmp(a, b) != 0)
	{
		fprintf(stderr,
				"%s: %s != %s (\"%s\" != \"%s\") (%s:%lu)\n",
				func, a_tok, b_tok, a, b, file, line);
		return (0);
	}
	return (1);
}
