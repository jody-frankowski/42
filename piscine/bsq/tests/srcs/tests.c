/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tests.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 14:17:46 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 14:17:47 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "libtest.h"

void	assert_equal_int(int a, int b)
{
	if (a != b)
	{
		ft_putnbr_fd(2, a);
		ft_putstr_fd(2, " and ");
		ft_putnbr_fd(2, b);
		ft_putstr_fd(2, " ARE NOT EQUAL\n");
		exit(-1);
	}
}

void	assert_equal_array(const void *s1, const void *s2, unsigned long n)
{
	if (ft_memcmp(s1, s2, n) != 0)
	{
		ft_putstr_fd(2, "THE FOLLOWING ARRAYS ARE NOT EQUAL\n");
		exit(-1);
	}
}

/*
** /!\ weird stuff can happen when comparing pointers
*/

void	assert_equal_ptr(const void *a, const void *b)
{
	if (a != b)
	{
		ft_putstr_fd(2, "ARE NOT EQUAL\n");
		exit(-1);
	}
}

void	assert_equal_str(char *s1, char *s2)
{
	if (ft_strcmp(s1, s2) != 0)
	{
		ft_putstr_fd(2, s1);
		ft_putstr_fd(2, " and \n");
		ft_putstr_fd(2, s2);
		ft_putstr_fd(2, " ARE NOT EQUAL\n");
		exit(-1);
	}
}
