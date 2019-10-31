#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"
#include "libunit.h"

void test_assert_mem_eq(void)
{
	char *test = "ABCDEFG";

	ASSERT_MEM_EQ(test, test+1, 5);
}

void test_assert_ptr_eq(void)
{
	char *test = "ABCDEFG";

	ASSERT_PTR_EQ(strchr(test, 'D'), strchr(test, 'C'));
}

void test_assert_str_eq(void)
{
	char *test = "ABCDEFG";

	ASSERT_STR_EQ(test, test+1);
}

void	test_bus_error(void)
{
	ASSERT_STR_EQ(NULL, "");
}

void	test_fd_capture(void)
{
	char *test = "ABCDE";
	char *output = NULL;

	ft_err_exit(start_fd_capture(1) != 0, "Failed to start fd capture!\n");
	write(1, test, 6);
	ft_err_exit(stop_fd_capture(1, &output) != 0, "Failed to stop fd capture!\n");
	ASSERT_MEM_EQ(test, output+1, 6);
	free(output);
}

void test_timeout(void)
{
	while (1)
		;
}

int	main(void)
{
	RUN_TEST(test_assert_mem_eq);
	RUN_TEST(test_assert_ptr_eq);
	RUN_TEST(test_assert_str_eq);
	RUN_TEST(test_bus_error);
	RUN_TEST(test_fd_capture);
	RUN_TEST(test_timeout);
}
