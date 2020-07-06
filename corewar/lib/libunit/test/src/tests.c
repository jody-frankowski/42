#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "libunit.h"

void test_assert(void)
{
	char *test = "ABCDEFG";
	ASSERT(strchr(test, 'D'), <, strchr(test, 'C'));
}

void test_assert_obj(void)
{
	char *test = "ABCDEFG";
	ASSERT_OBJ(strcmp, test, "BCDEFG", == 0, ft_putstr_fd);
}

void test_assert_nobj(void)
{
	char *test = "ABCDEFG";
	ASSERT_NOBJ(memcmp, test, "BCDEFG", 6, == 0, ft_hexdump_fd);
}

void	test_crash(void)
{
	int *test = NULL;
	test[0] = 1;
}

void	test_fd_capture(void)
{
	char *test;
	char *output;
	int ret;
	// /!\ Do not add a line return in test, because doing so would make libc's
	// printf flush its buffers, making the printf test useless.
	test = "ABCDE";

	// Simple write() test
	output = NULL;
	ft_err_exit(start_fd_capture(1) == -1, "Failed to start fd capture!\n");
	write(1, test, strlen(test));
	ft_err_exit((ret = stop_fd_capture(1, &output)) == -1, "Failed to stop fd capture!\n");
	ASSERT(ret, ==, (int)strlen(test));
	ASSERT_NOBJ(memcmp, test, output+1, ret - 1, == 0, ft_hexdump_fd);
	free(output);

	// printf() test
	output = NULL;
	ft_err_exit(start_fd_capture(1) == -1, "Failed to start fd capture!\n");
	printf("%s", test);
	ft_err_exit((ret = stop_fd_capture(1, &output)) == -1, "Failed to stop fd capture!\n");
	ASSERT(ret, ==, (int)strlen(test));
	ASSERT_NOBJ(memcmp, test, output+1, ret - 1, == 0, ft_hexdump_fd);
	free(output);
}

void test_timeout(void)
{
	while (1)
		;
}

int	main(void)
{
	RUN_TEST(test_assert);
	RUN_TEST(test_assert_obj);
	RUN_TEST(test_assert_nobj);
	RUN_TEST(test_crash);
	RUN_TEST(test_fd_capture);
	RUN_TEST(test_timeout);
}
