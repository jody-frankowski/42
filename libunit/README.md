# `libunit` - A Better Unit Tests Library (Current)

Subject: [libunit.en.pdf](libunit.en.pdf)

The goal of this project was to write a library that helps writing unit tests
along with some example unit tests.
However the subject was uselessly too large/strict in its requirements:

  - one file per test
  - one directory for every function tested
  - a launcher for every directory
  - a main that calls all the launchers
  - mandatory handling of series of tests
  - mandatory printing for both passed and failed tests

Instead I chose to spend my time on the fork, signal catching, output capturing
and api. So this repository doesn't represent what was asked for the project.

The main purpose of the library and wrapper macros is to see the value of the
things that were checked right away.
Because this library focuses on printing informations when tests fail, it
doesn't print anything when tests pass.

So, no output == GOOD, output == BAD. Simple.

## API

```c
// Wrap a test function in order to catch crashes and timeouts
RUN_TEST(function);

// Assert that some primitive object compares to another (pointer, int, char)
ASSERT(left, condition, right);

// Assert that some object compares to another
// The cmp_function function is called like so: cmp_function(left, right)
// The printf_function function is called like so:
// print_function(file descriptor, left|right)
ASSERT_OBJ(cmp_function, left, right, condition, print_function);

// Assert that some object compares to another
// The cmp_function function is called like so: cmp_function(left, right, len)
// The printf_function function is called like so:
// print_function(file descriptor, left|right, len)
ASSERT_NOBJ(cmp_function, left, right, len, condition, print_function);

// Start capturing the data written to fd
start_fd_capture(int fd);

// Stop capturing the data written to fd and write it to *output
stop_fd_capture(int fd, char **output);
```

## Examples

Test:

```c
void test_assert(void)
{
	char *test = "ABCDEFG";
	ASSERT(strchr(test, 'D'), <, strchr(test, 'C'));
}
```

Output:

```
test_assert@(src/tests.c:9): strchr(test, 'D') !< strchr(test, 'C') (0x56112c95f013 !< 0x56112c95f012)
```

Test:

```c
void test_assert_obj(void)
{
	char *test = "ABCDEFG";
	ASSERT_OBJ(strcmp, test, "BCDEFG", == 0, ft_putstr_fd);
}
```

```
test_assert_obj@(src/tests.c:15): strcmp(test, "BCDEFG") !== 0:
ABCDEFG
BCDEFG
```

Test:

```c
void test_assert_nobj(void)
{
	char *test = "ABCDEFG";
	ASSERT_NOBJ(memcmp, test, "BCDEFG", 6, == 0, ft_hexdump_fd);
}
```

Output:

```
test_assert_nobj@(src/tests.c:21): memcmp(test, "BCDEFG") !== 0:
41 42 43 44 45 46 ABCDEF

42 43 44 45 46 47 BCDEFG

```

Test:

```c
void	test_crash(void)
{
	int *test = NULL;
	test[0] = 1;
}
```

Output:

```
test_crash@(src/tests.c:69): Segmentation fault
```

Test:

```c
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
```

Output:

```
test_fd_capture@(src/tests.c:45): memcmp(test, output+1) !== 0:
41 42 43 44 ABCD

42 43 44 45 BCDE

test_fd_capture@(src/tests.c:54): memcmp(test, output+1) !== 0:
41 42 43 44 ABCD

42 43 44 45 BCDE

```

Test:

```c
void test_timeout(void)
{
	while (1)
		;
}
```

Output:

```
test_timeout@(src/tests.c:71): Timeout
```

And the wrapper that calls all these tests:

```c
int	main(void)
{
	RUN_TEST(test_assert);
	RUN_TEST(test_assert_obj);
	RUN_TEST(test_assert_nobj);
	RUN_TEST(test_crash);
	RUN_TEST(test_fd_capture);
	RUN_TEST(test_timeout);
}
```

You can find an up-to-date version of theses examples in
[test/src/tests.c](test/src/tests.c).
