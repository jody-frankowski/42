#include <ctype.h>
#include <stdio.h>
#include <string.h>

void	print_hex(const void *data, int n)
{
	int i;

	const unsigned char *d = (const unsigned char*)data;
	i = 0;
	while (i < n)
	{
		printf("%02x ", d[i]);
		i++;
	}
	i = 0;
	while (i < n)
	{
		if (isprint(d[i]))
			printf("%c", d[i]);
		else
			printf(".");
		i++;
	}
	printf("\n");
}

int assert_false(const char *a_tok, const char *file, const char *func, size_t line, int a)
{
	if (a)
	{
		printf("%s:%s:%lu: assertation failed: %s is not false (%d)\n", file, func, line, a_tok, a);
		return (0);
	}
	return (1);
}

int assert_true(const char *a_tok, const char *file, const char *func, size_t line, int a)
{
	if (!a)
	{
		printf("%s:%s:%lu: assertation failed: %s is not true (%d)\n", file, func, line, a_tok, a);
		return (0);
	}
	return (1);
}

int assert_equal_bool(const char *a_tok, const char *b_tok, const char *file, const char *func, size_t line, int a, int b)
{
	if (!((a == 0 && b == 0) || (a != 0 && b != 0)))
	{
		printf("%s:%s:%lu: bool assertation failed: %s != %s (%d != %d)\n", file, func, line, a_tok, b_tok, a, b);
		return (0);
	}
	return (1);
}

int assert_equal_int(const char *a_tok, const char *b_tok, const char *file, const char *func, size_t line, int a, int b)
{
	if (a != b)
	{
		printf("%s:%s:%lu: assertation failed: %s != %s (%d != %d)\n", file, func, line, a_tok, b_tok, a, b);
		return (0);
	}
	return (1);
}

int assert_equal_mem(const char *a_tok, const char *b_tok, const char *file, size_t line, const void *a, const void *b, size_t n)
{
	if (memcmp(a, b, n) != 0)
	{
		printf("%s:%lu: assertation failed: %s != %s\n", file, line, a_tok, b_tok);
		print_hex(a, n);
		printf("\n");
		print_hex(b, n);
		printf("\n");
		return (0);
	}
	return (1);
}

int assert_equal_ptr(const char *a_tok, const char *b_tok, const char *file, const char *func, size_t line, const void *a, const void *b)
{
	if (a != b)
	{
		printf("%s:%s:%lu: assertation failed: %s != %s (%p != %p)\n", file, func, line, a_tok, b_tok, a, b);
		return (0);
	}
	return (1);
}

int assert_equal_str(const char *a_tok, const char *b_tok, const char *file, const char *func, size_t line, const char *a, const char *b)
{
	if (strcmp(a, b) != 0)
	{
		printf("%s:%s:%lu: assertation failed: %s != %s (\"%s\" != \"%s\")\n", file, func, line, a_tok, b_tok, a, b);
		return (0);
	}
	return (1);
}

int assert_not_equal_int(const char *a_tok, const char *b_tok, const char *file, const char *func, size_t line, int a, int b)
{
	if (a == b)
	{
		printf("%s:%s:%lu: assertation failed: %s == %s (%d == %d)\n", file, func, line, a_tok, b_tok, a, b);
		return (0);
	}
	return (1);
}

int assert_not_equal_mem(const char *a_tok, const char *b_tok, const char *file, size_t line, const void *a, const void *b, size_t n)
{
	if (memcmp(a, b, n) == 0)
	{
		printf("%s:%lu: assertation failed: %s == %s\n", file, line, a_tok, b_tok);
		print_hex(a, n);
		printf("\n");
		print_hex(b, n);
		printf("\n");
		return (0);
	}
	return (1);
}

int assert_not_equal_ptr(const char *a_tok, const char *b_tok, const char *file, const char *func, size_t line, const void *a, const void *b)
{
	if (a == b)
	{
		printf("%s:%s:%lu: assertation failed: %s == %s (%p == %p)\n", file, func, line, a_tok, b_tok, a, b);
		return (0);
	}
	return (1);
}

int assert_not_equal_str(const char *a_tok, const char *b_tok, const char *file, const char *func, size_t line, const char *a, const char *b)
{
	if (strcmp(a, b) == 0)
	{
		printf("%s:%s:%lu: assertation failed: %s == %s (\"%s\" == \"%s\")\n", file, func, line, a_tok, b_tok, a, b);
		return (0);
	}
	return (1);
}
