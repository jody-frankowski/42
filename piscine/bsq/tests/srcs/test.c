/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 16:28:00 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 16:28:01 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "libtest.h"

void	test_get_spec(void)
{
	t_spec *spec;

	spec = get_spec("42.ox");
	assert_equal_int(spec->l, 42);
	assert_equal_array(&(spec->empty), ".", 1);
	assert_equal_array(&(spec->obstacle), "o", 1);
	assert_equal_array(&(spec->full), "x", 1);
}

void	test_spec_valid(void)
{
	assert_equal_int(1, spec_valid("50ABC"));
	assert_equal_int(1, spec_valid("50.ox"));
	assert_equal_int(0, spec_valid("+2.ox"));
	assert_equal_int(0, spec_valid("0.ox"));
	assert_equal_int(0, spec_valid("-42.ox"));
	assert_equal_int(0, spec_valid("50scoobydoo.ox"));
	assert_equal_int(0, spec_valid("..ox"));
	assert_equal_int(0, spec_valid("5"));
}

void	test_realloc(void)
{
	char *new;
	char *test;

	test = ft_strdup("HELLO");
	new = (char *)ft_realloc(test, 10);
	assert_equal_str(new, "HELLO");
	new = (char *)ft_realloc(new, 3);
	assert_equal_array(new, "HEL", 3);
}

int		main(void)
{
	test_spec_valid();
	test_get_spec();
	test_realloc();
	return (0);
}
