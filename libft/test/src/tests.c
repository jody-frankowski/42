#ifdef __linux__
# ifndef _GNU_SOURCE
#  define _GNU_SOURCE
# endif
#endif

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bigint.h"
#include "libft.h"
#include "libtest.h"
#include "libunit.h"

void test_ft_atoi()
{
	unsigned long i;
	char *tests[] = {
		/* Garbage */
		/* NULL, */
		"\t\n\v\f\r -42",
		"--42",
		"++42",
		"42sh",
		"AAAA",
		"    ",
		"0x42",
		/* LONG */
		"-9223372036854775808",
		/* underflow */
		"-9223372036854775809",
		"9223372036854775807",
		/* overflow */
		"9223372036854775808",
		/* INT */
		"-2147483648",
		"-2147483649",
		"2147483647",
		"2147483648",
		/* Others */
		"+42",
		"-11",
		"-10",
		"-1",
		"0",
		"1",
		"9",
		"10",
		"11",
		"",
	};
	i = 0;
	while (i < sizeof(tests)/sizeof(tests[0]))
	{
		if (!ASSERT_EQUAL_INT(atoi(tests[i]), ft_atoi(tests[i])))
			printf("%s is wrong!\n", tests[i]);
		i++;
	}
}

void test_ft_strtol()
{
	unsigned long i;
	unsigned long j;
	char *tests[] = {
		/* Garbage */
		/* NULL, */
		"\t\n\v\f\r -42",
		"--42",
		"++42",
		"42sh",
		"    ",
		"    -0.",
		"    0.",
		/* Hex */
		"AAAA",
		"abdDCE",
		"abcdefg",
		"0x42",
		"0X42",
		/* Octal */
		"0774",
		"0888",
		/* LONG */
		"-9223372036854775808",
		/* underflow */
		"-9223372036854775809",
		"9223372036854775807",
		/* overflow */
		"9223372036854775808",
		/* INT */
		"-2147483648",
		"-2147483649",
		"2147483647",
		"2147483648",
		/* Others */
		"+42",
		"-11",
		"-10",
		"-1",
		"0",
		"1",
		"9",
		"10",
		"11",
		"",
	};
	char *endptr;
	char *ft_endptr;

	i = 0;
	while (i < sizeof(tests)/sizeof(tests[0]))
	{
		// Test all valid bases: 0 and 2 to 36. We have a different behavior for
		// the endptr for the bases 1 and 37+ but that's not important because
		// they aren't valid bases anyway.
		j = 0;
		while (j <= 36)
		{
			if (j == 1)
			{
				j++;
				continue;
			}

			if (!ASSERT_EQUAL_INT(strtol(tests[i], &endptr, j), ft_strtol(tests[i], &ft_endptr, j)))
				printf("|%s| with base %lu is wrong!\n", tests[i], j);
			if (!ASSERT_EQUAL_PTR(endptr, ft_endptr))
				printf("|%s| with base %lu is wrong!\nptr: |%s| ft_ptr: |%s|\n", tests[i], j, endptr, ft_endptr);
			j++;
		}
		i++;
	}
}

void test_ft_charcasecmp()
{
	size_t i;

	i = 0;
	while (i < 26)
	{
		ASSERT_EQUAL_INT(0, ft_charcasecmp('a'+i, 'A'+i));
		ASSERT_EQUAL_INT(1, ft_charcasecmp('a'+i+1, 'A'+i));
		i++;
	}
	i = 0;
	while (i < 127)
	{
		ASSERT_EQUAL_INT(0, ft_charcasecmp(i, i));
		i++;
	}
}

void test_ft_count_words()
{
	ASSERT_EQUAL_INT(0, ft_count_words("", ""));
	ASSERT_EQUAL_INT(0, ft_count_words("", "A"));
	ASSERT_EQUAL_INT(0, ft_count_words(" ", " "));
	ASSERT_EQUAL_INT(1, ft_count_words("A", ""));
	ASSERT_EQUAL_INT(1, ft_count_words("A", " "));
	ASSERT_EQUAL_INT(1, ft_count_words("AAA", " "));
	ASSERT_EQUAL_INT(2, ft_count_words(" A A ", " "));
	ASSERT_EQUAL_INT(2, ft_count_words("#AB/.ABCD...", "#./"));
}

void test_ft_count_words_c()
{
	ASSERT_EQUAL_INT(0, ft_count_words_c("", '\0'));
	ASSERT_EQUAL_INT(0, ft_count_words_c("", 'A'));
	ASSERT_EQUAL_INT(0, ft_count_words_c(" ", ' '));
	ASSERT_EQUAL_INT(1, ft_count_words_c("A", '\0'));
	ASSERT_EQUAL_INT(1, ft_count_words_c("A", ' '));
	ASSERT_EQUAL_INT(1, ft_count_words_c("AAA", ' '));
	ASSERT_EQUAL_INT(2, ft_count_words_c(" A A ", ' '));
}

void test_ft_incharset()
{
	char *test = "abcdABCD";

	ASSERT_TRUE(ft_incharset('a', test));
	ASSERT_TRUE(ft_incharset('D', test));
	ASSERT_FALSE(ft_incharset('E', test));
	ASSERT_FALSE(ft_incharset('\0', test));
}

void test_ft_isspace()
{
	char test;

	test = -128;
	while (test < 127)
	{
		ASSERT_EQUAL_BOOL(isspace(test), ft_isspace(test));
		test++;
	}
}

void test_ft_itoa()
{
	struct data
	{
		char *expected;
		int input;
	};
	unsigned long i;
	struct data tests[] =
	{
		{"-42", -42},
		{"-10", -10},
		{"-1", -1},
		{"0", 0},
		{"1", 1},
		{"10", 10},
		{"42", 42},
		{"-1337", -1337},
		{"-2147483648", -2147483648},
		{"2147483647", 2147483647}
	};
	char *result;

	i = 0;
	while (i < sizeof(tests)/sizeof(tests[0]))
	{
		result = ft_itoa(tests[i].input);
		ASSERT_EQUAL_STR(tests[i].expected, result);
		free(result);
		i++;
	}
}

void test_ft_stpncpy()
{
	char src[10];
	char orig_dst[10];
	char ft_dst[10];
	char *ft_ptr;
	char *orig_ptr;
	int i;
	int j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			memset(orig_dst, 'B', 10);
			memset(ft_dst, 'B', 10);
			memset(src, '\0', 10);
			memset(src, 'A', i);
			orig_ptr = stpncpy(orig_dst, src, j);
			ft_ptr = ft_stpncpy(ft_dst, src, j);

			if (!ASSERT_EQUAL_INT(orig_ptr - orig_dst, ft_ptr - ft_dst))
				printf("i: %d, j: %d\n", i, j);
			/* ASSERT_EQUAL_INT(orig_ptr - orig_dst, ft_ptr - ft_dst, "i: %d, j: %d", i, j); */
			ASSERT_EQUAL_MEM(orig_dst, ft_dst, 10);
			j++;
		}
		i++;
	}
}

void test_ft_strcasecmp()
{
	ASSERT_EQUAL_INT(strcasecmp("TEST", "test"), ft_strcasecmp("TEST", "test"));
	ASSERT_EQUAL_INT(strcasecmp("TEST", "TEST"), ft_strcasecmp("TEST", "TEST"));
	ASSERT_EQUAL_INT(strcasecmp("AAAA", "AABB"), ft_strcasecmp("AAAA", "AABB"));
}

void test_ft_strncasecmp()
{
	size_t i;

	i = 0;
	while (i < 6)
	{
		ASSERT_EQUAL_INT(strncasecmp("TEST", "test", i), ft_strncasecmp("TEST", "test", i));
		ASSERT_EQUAL_INT(strncasecmp("TEST", "TEST", i), ft_strncasecmp("TEST", "TEST", i));
		ASSERT_EQUAL_INT(strncasecmp("AAAA", "AABB", i), ft_strncasecmp("AAAA", "AABB", i));
		i++;
	}
}

void test_ft_strcasestr()
{
	char *haystack = "TesT AAAA!!";

	ASSERT_EQUAL_PTR(strcasestr(haystack, "test"), ft_strcasestr(haystack, "test"));
	ASSERT_EQUAL_PTR(strcasestr(haystack, "TEST"), ft_strcasestr(haystack, "TEST"));
	ASSERT_EQUAL_PTR(strcasestr(haystack, "tESt"), ft_strcasestr(haystack, "tESt"));
	ASSERT_EQUAL_PTR(strcasestr(haystack, "aaaa"), ft_strcasestr(haystack, "aaaa"));
	ASSERT_EQUAL_PTR(strcasestr(haystack, "bbbb"), ft_strcasestr(haystack, "bbbb"));
	ASSERT_EQUAL_PTR(strcasestr(haystack, "!!"), ft_strcasestr(haystack, "!!"));
}

void test_ft_strlcpy()
{
	char src[10];
	char orig_dst[10];
	char ft_dst[10];
	int i;
	int j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			memset(orig_dst, 'B', 10);
			memset(ft_dst, 'B', 10);
			memset(src, '\0', 10);
			memset(src, 'A', i);

			if (!ASSERT_EQUAL_INT(strlcpy(orig_dst, src, j), ft_strlcpy(ft_dst, src, j)))
				printf("i: %d, j: %d\n", i, j);
			/* ASSERT_EQUAL_INT(orig_ptr - orig_dst, ft_ptr - ft_dst, "i: %d, j: %d", i, j); */
			ASSERT_EQUAL_MEM(orig_dst, ft_dst, 10);
			j++;
		}
		i++;
	}

}

void test_ft_strndup()
{
	const char *test = "1234";
	char *dup;
	char *ft_dup;
	int i;

	i = 0;
	while (i < 5)
	{
		dup = strndup(test, i);
		ft_dup = ft_strndup(test, i);
		ASSERT_EQUAL_MEM(dup, ft_dup, i);
		free(dup);
		free(ft_dup);
		i++;
	}
}

void test_ft_strnlen()
{
	const char *test = "1234";

	ASSERT_EQUAL_INT(strnlen(test, 0), ft_strnlen(test, 0));
	ASSERT_EQUAL_INT(strnlen(test, 4), ft_strnlen(test, 4));
	ASSERT_EQUAL_INT(strnlen(test, 5), ft_strnlen(test, 5));
	ASSERT_EQUAL_INT(strnlen(test, 6), ft_strnlen(test, 6));
	// TODO catch segfault
	/* srcs/tests.c:35:19: error: null argument where non-null required (argument 1) [-Werror=nonnull] */
	/* 	assert_equal_int(strnlen(NULL, 5), ft_strnlen(NULL, 5)); */
	/* assert_equal_int(strnlen(NULL, 5), ft_strnlen(NULL, 5)); */
}

void test_ft_strpbrk()
{
	ASSERT_EQUAL_PTR(strpbrk("ABCD", "ABCD"), ft_strpbrk("ABCD", "ABCD"));
	ASSERT_EQUAL_PTR(strpbrk("ABCD", "BCD"), ft_strpbrk("ABCD", "BCD"));
	ASSERT_EQUAL_PTR(strpbrk("ABCD", "EFG"), ft_strpbrk("ABCD", "EFG"));
	ASSERT_EQUAL_PTR(strpbrk("", "BCD"), ft_strpbrk("", "BCD"));
	ASSERT_EQUAL_PTR(strpbrk("ABCD", ""), ft_strpbrk("ABCD", ""));
}


void test_ft_tab_push_ptr_free(void *ptr)
{
	free(*(void **)ptr);
}

void test_ft_tab_push_ptr()
{
	char **test;

	test = NULL;
	ft_tab_push_ptr((void **)&test, ft_strdup("123"), sizeof(*test), 0);
	ASSERT_EQUAL_STR("123", test[0]);
	ft_tab_push_ptr((void **)&test, ft_strdup("456"), sizeof(*test), 1);
	ASSERT_EQUAL_STR("123", test[0]);
	ASSERT_EQUAL_STR("456", test[1]);
	ft_tab_push_ptr((void **)&test, ft_strdup("789"), sizeof(*test), 2);
	ASSERT_EQUAL_STR("123", test[0]);
	ASSERT_EQUAL_STR("456", test[1]);
	ASSERT_EQUAL_STR("789", test[2]);
	ft_tab_free(test, &test_ft_tab_push_ptr_free, sizeof(*test), 3);
}

void test_ft_strsplit_free(void *ptr)
{
	free(*(void **)ptr);
}

void test_ft_strsplit()
{
	char **words;

	words = ft_strsplit(" 1 2 3 ", ' ');
	ASSERT_EQUAL_STR("1", words[0]);
	ASSERT_EQUAL_STR("2", words[1]);
	ASSERT_EQUAL_STR("3", words[2]);
	ASSERT_EQUAL_PTR(NULL, words[3]);
	ft_tab_free((void **)words, &test_ft_strsplit_free, sizeof(*words), 4);

	words = ft_strsplit("WORD", ' ');
	ASSERT_EQUAL_STR("WORD", words[0]);
	ASSERT_EQUAL_PTR(NULL, words[1]);
	ft_tab_free((void **)words, &test_ft_strsplit_free, sizeof(*words), 2);

	words = ft_strsplit(" WORD", ' ');
	ASSERT_EQUAL_STR("WORD", words[0]);
	ASSERT_EQUAL_PTR(NULL, words[1]);
	ft_tab_free((void **)words, &test_ft_strsplit_free, sizeof(*words), 2);

	words = ft_strsplit(" WORD ", ' ');
	ASSERT_EQUAL_STR("WORD", words[0]);
	ASSERT_EQUAL_PTR(NULL, words[1]);
	ft_tab_free((void **)words, &test_ft_strsplit_free, sizeof(*words), 2);

	words = ft_strsplit("WORD ", ' ');
	ASSERT_EQUAL_STR("WORD", words[0]);
	ASSERT_EQUAL_PTR(NULL, words[1]);
	ft_tab_free((void **)words, &test_ft_strsplit_free, sizeof(*words), 2);

	words = ft_strsplit("", ' ');
	ASSERT_EQUAL_PTR(NULL, words[0]);
	ft_tab_free((void **)words, &test_ft_strsplit_free, sizeof(*words), 1);

	words = ft_strsplit(" ", ' ');
	ASSERT_EQUAL_PTR(NULL, words[0]);
	ft_tab_free((void **)words, &test_ft_strsplit_free, sizeof(*words), 1);
}

void test_ft_strrev()
{
	unsigned long i;
	char *tests[][2] = {
		{"", ""},
		{"A", "A"},
		{"ABCD", "DCBA"}
	};
	char *rev;

	i = 0;
	while (i < sizeof(tests)/sizeof(tests[0]))
	{
		rev = ft_strrev(tests[i][0]);
		ASSERT_EQUAL_STR(tests[i][1], rev);
		free(rev);
		i++;
	}
}

void test_ft_num_digits()
{
	ASSERT_EQUAL_INT(1, ft_num_digits(0));
	ASSERT_EQUAL_INT(2, ft_num_digits(-10));
	ASSERT_EQUAL_INT(2, ft_num_digits(10));
	ASSERT_EQUAL_INT(2, ft_num_digits(99));
}

void test_ft_pow()
{
	ASSERT_EQUAL_INT(1, ft_pow(0, 0));
	ASSERT_EQUAL_INT(1, ft_pow(10, 0));
	ASSERT_EQUAL_INT(10, ft_pow(10, 1));
	ASSERT_EQUAL_INT(100, ft_pow(10, 2));
	ASSERT_EQUAL_INT(27, ft_pow(3, 3));
	ASSERT_EQUAL_INT(-27, ft_pow(-3, 3));
	ASSERT_EQUAL_INT(9, ft_pow(3, 2));
}

void test_ft_strspn()
{
	ASSERT_EQUAL_INT(0, ft_strspn("   ", "ab"));
	ASSERT_EQUAL_INT(0, ft_strspn("", "ab"));
	ASSERT_EQUAL_INT(0, ft_strspn("", ""));
	ASSERT_EQUAL_INT(0, ft_strspn("ab", ""));
	ASSERT_EQUAL_INT(1, ft_strspn(" a  ", " "));
	ASSERT_EQUAL_INT(3, ft_strspn("123", "123"));
	ASSERT_EQUAL_INT(1, ft_strspn("123", "13"));
}

void test_ft_strcspn()
{
	ASSERT_EQUAL_INT(3, ft_strcspn("123", "ab"));
	ASSERT_EQUAL_INT(0, ft_strcspn("", "ab"));
	ASSERT_EQUAL_INT(0, ft_strcspn("", ""));
	ASSERT_EQUAL_INT(2, ft_strcspn("ab", ""));
	ASSERT_EQUAL_INT(0, ft_strcspn(" a  ", " "));
	ASSERT_EQUAL_INT(0, ft_strcspn("123", "123"));
	ASSERT_EQUAL_INT(1, ft_strcspn("123", "2"));
}

void test_ft_strsub()
{
	char *sub;

	sub = ft_strsub("TEST", 0, 0);
	ASSERT_EQUAL_STR("", sub); free(sub);
	/* This test breaks clang's AddressSanitizer */
	/* ASSERT_EQUAL_PTR(NULL, ft_strsub("TEST", 0, -10)); */
}

/*
** ft_lst* helper
*/

void lstfreeone(void *content, __attribute__((unused)) size_t size)
{
	free(content);
}

/*
** test_ft_lstissorted and test_ft_lstmergesort helper
*/

int lstcmp(t_list *a, t_list *b)
{
	if (!a || !b)
		return (0);
	return (strcmp(a->content, b->content));
}

void test_ft_lstissorted()
{
	t_list *test;

	test = NULL;
	ft_lstpush(&test, ft_lstnew("BBBB", 5));
	ASSERT_TRUE(ft_lstissorted(test, lstcmp));
	ft_lstpush(&test, ft_lstnew("CCCC", 5));
	ASSERT_TRUE(ft_lstissorted(test, lstcmp));
	ft_lstpush(&test, ft_lstnew("AAAA", 5));
	ASSERT_FALSE(ft_lstissorted(test, lstcmp));

	ft_lstdel(&test, lstfreeone);
}

void test_ft_lstfree()
{
	t_list *test;
	t_list *save;

	test = NULL;
	ft_lstpush(&test, ft_lstnew("ABCD", 5));
	ft_lstfree(&test, test->content);
	ASSERT_EQUAL_PTR(NULL, test);

	ft_lstpush(&test, ft_lstnew("ABCD", 5));
	ft_lstpush(&test, ft_lstnew("1234", 5));
	save = test->next;
	ft_lstfree(&test, test->content);
	ASSERT_EQUAL_PTR(save, test);
	ASSERT_EQUAL_PTR(NULL, test->next);
	ft_lstdel(&test, lstfreeone);

	ft_lstpush(&test, ft_lstnew("1234", 5));
	ft_lstpush(&test, ft_lstnew("ABCD", 5));
	ft_lstpush(&test, ft_lstnew("5678", 5));
	ft_lstfree(&test, test->next->content);
	ASSERT_EQUAL_STR("1234", test->content);
	ASSERT_EQUAL_STR("5678", test->next->content);

	ft_lstdel(&test, lstfreeone);
}

void test_ft_lstmergesort()
{
	t_list *test;

	test = NULL;
	ft_lstpush(&test, ft_lstnew("AAAA", 5));
	ft_lstpush(&test, ft_lstnew("BBBB", 5));
	ft_lstpush(&test, ft_lstnew("CCCC", 5));
	ft_lstmergesort(&test, lstcmp);
	ASSERT_TRUE(ft_lstissorted(test, lstcmp));
	ft_lstdel(&test, lstfreeone);

	ft_lstpush(&test, ft_lstnew("CCCC", 5));
	ft_lstpush(&test, ft_lstnew("BBBB", 5));
	ft_lstpush(&test, ft_lstnew("AAAA", 5));
	ft_lstmergesort(&test, lstcmp);
	ASSERT_TRUE(ft_lstissorted(test, lstcmp));
	ft_lstdel(&test, lstfreeone);

	ft_lstpush(&test, ft_lstnew("CCCC", 5));
	ft_lstpush(&test, ft_lstnew("BBBB", 5));
	ft_lstpush(&test, ft_lstnew("BBBB", 5));
	ft_lstpush(&test, ft_lstnew("AAAA", 5));
	ft_lstmergesort(&test, lstcmp);
	ASSERT_TRUE(ft_lstissorted(test, lstcmp));
	ft_lstdel(&test, lstfreeone);

	ft_lstpush(&test, ft_lstnew("CCCC", 5));
	ft_lstpush(&test, ft_lstnew("AAAA", 5));
	ft_lstpush(&test, ft_lstnew("BBBB", 5));
	ft_lstmergesort(&test, lstcmp);
	ASSERT_TRUE(ft_lstissorted(test, lstcmp));
	ft_lstdel(&test, lstfreeone);

	ft_lstpush(&test, ft_lstnew("AAAA", 5));
	ft_lstpush(&test, ft_lstnew("CCCC", 5));
	ft_lstpush(&test, ft_lstnew("BBBB", 5));
	ft_lstmergesort(&test, lstcmp);
	ASSERT_TRUE(ft_lstissorted(test, lstcmp));
	ft_lstdel(&test, lstfreeone);

	ft_lstpush(&test, ft_lstnew("AAAA", 5));
	ft_lstpush(&test, ft_lstnew("CCCC", 5));
	ft_lstpush(&test, ft_lstnew("BBBB", 5));
	ft_lstpush(&test, ft_lstnew("BBBB", 5));
	ft_lstmergesort(&test, lstcmp);
	ASSERT_TRUE(ft_lstissorted(test, lstcmp));
	ft_lstdel(&test, lstfreeone);
}

void test_ft_lstpush()
{
	t_list *test;

	test = NULL;
	ft_lstpush(&test, ft_lstnew("AAAA", 5));
	ASSERT_NOT_EQUAL_PTR(NULL, test);
	ASSERT_EQUAL_STR(test->content, "AAAA");
	ASSERT_EQUAL_PTR(NULL, test->next);
	ft_lstpush(&test, ft_lstnew("BBBB", 5));
	ASSERT_NOT_EQUAL_PTR(NULL, test);
	ASSERT_EQUAL_STR(test->content, "AAAA");
	ASSERT_EQUAL_STR(test->next->content, "BBBB");
	ASSERT_EQUAL_PTR(NULL, test->next->next);
	ft_lstdel(&test, lstfreeone);
}

/*
** test_ft_lstmap helper
*/

t_list *lstmap(t_list *elem)
{
	t_list *new;
	char *rev;

	rev = ft_strrev((char *)elem->content);
	new = ft_lstnew(rev, elem->content_size);
	free(rev);
	return (new);
}

void test_ft_lstmap()
{
	t_list *old;
	t_list *new;

	old = NULL;
	ft_lstpush(&old, ft_lstnew("ABCD", 5));
	ft_lstpush(&old, ft_lstnew("1234", 5));
	ft_lstpush(&old, ft_lstnew("6789", 5));
	new = ft_lstmap(old, lstmap);
	ASSERT_NOT_EQUAL_PTR(new, old);
	ASSERT_EQUAL_STR("DCBA", new->content);
	ASSERT_EQUAL_STR("4321", new->next->content);
	ASSERT_EQUAL_STR("9876", new->next->next->content);
	ASSERT_EQUAL_PTR(NULL,   new->next->next->next);
	ft_lstdel(&old, lstfreeone);
	ft_lstdel(&new, lstfreeone);
}

void test_ft_swap()
{
	void *a = strdup("123456789");
	void *b = strdup("ABCDEFGHI");

	ft_swap(a, b, 10);
	ASSERT_EQUAL_STR("ABCDEFGHI", a);
	ASSERT_EQUAL_STR("123456789", b);
	ft_swap(a, b, 3);
	ASSERT_EQUAL_STR("123DEFGHI", a);
	ASSERT_EQUAL_STR("ABC456789", b);
	free(a);
	free(b);
}

int charcmp(const void *a, const void *b)
{
	return (*(unsigned char*)a - *(unsigned char*)b);
}

void test_ft_issorted()
{
	char *sorted = "abcdefg";
	char *not_sorted = "abdcefg";

	ASSERT_TRUE(ft_issorted(sorted, strlen(sorted), 1, charcmp));
	ASSERT_FALSE(ft_issorted(not_sorted, strlen(not_sorted), 1, charcmp));
}

void test_ft_qsort()
{
	char *not_sorted;

	not_sorted = ft_strdup("abdcefg");
	ft_qsort(not_sorted, strlen(not_sorted), 1, charcmp);
	ASSERT_TRUE(ft_issorted(not_sorted, strlen(not_sorted), 1, charcmp));
	free(not_sorted);
	not_sorted = ft_strdup("gfheiasdflkjnbv...");
	ft_qsort(not_sorted, strlen(not_sorted), 1, charcmp);
	ASSERT_TRUE(ft_issorted(not_sorted, strlen(not_sorted), 1, charcmp));
	free(not_sorted);
	not_sorted = ft_strdup("DDDDDAAAAAA");
	ft_qsort(not_sorted, strlen(not_sorted), 1, charcmp);
	ASSERT_TRUE(ft_issorted(not_sorted, strlen(not_sorted), 1, charcmp));
	free(not_sorted);
}

void test_ft_bstrdup()
{
	char *dup;

	ASSERT_EQUAL_PTR(NULL, ft_bstrdup(NULL, 10));
	dup = ft_bstrdup("test", 0);
	ASSERT_EQUAL_MEM(dup, "", 1);
	free(dup);
	dup = ft_bstrdup(&(int []){0x0, 0x1, 0x2}, 3);
	ASSERT_EQUAL_MEM(dup, (&(int []){0x0, 0x1, 0x2, 0x0}), 4);
	free(dup);
}

void test_ft_bstrtrunc()
{
	char *test;

	test = NULL;
	// returns 0 when src == NULL
	ASSERT_EQUAL_INT(0, ft_bstrtrunc(NULL, 1, 2));
	// returns 0 when *src == NULL
	ASSERT_EQUAL_INT(0, ft_bstrtrunc((void **)&test, 1, 2));
	test = malloc(1);
	test[0] = 0x1;
	// returns 1 when len == 0
	ASSERT_EQUAL_INT(1, ft_bstrtrunc((void **)&test, 0, 0));
	// Only 1 NULL byte when len == 0
	ASSERT_EQUAL_MEM(test, &(char []){0x0}, 1);

	free(test);
	test = malloc(3);
	test[0] = 0x1;
	test[1] = 0x0;
	test[2] = 0x2;
	ASSERT_EQUAL_INT(1, ft_bstrtrunc((void **)&test, 1, 2));
	ASSERT_EQUAL_MEM(test, (&(char []){0x0, 0x2, 0x0}), 3);
	free(test);
}

void test_ft_array_new()
{
	t_array *array;

	array = ft_array_new(sizeof(int), &free);

	ASSERT_EQUAL_PTR(array->bytes, NULL);
	ASSERT_EQUAL_PTR(array->free, free);
	ASSERT_EQUAL_INT(array->len, 0);
	ASSERT_EQUAL_INT(array->width, sizeof(int));
	ft_array_free(array);
}

void array_free_helper(void *data)
{
	free(*(void **)data);
}

void test_ft_array_push()
{
	t_array *array;

	array = ft_array_new(sizeof(int), NULL);
	ft_array_push(array, &(int[]){42});
	ASSERT_EQUAL_INT(*(int *)ft_array_get(array, 0), 42);
	ft_array_free(array);

	array = ft_array_new(sizeof(char *), array_free_helper);
	ft_array_push_ptr(array, strdup("test"));
	ASSERT_EQUAL_INT(array->len, 1);
	ASSERT_EQUAL_STR(*(char **)ft_array_get(array, 0), "test");

	ft_array_push_ptr(array, strdup("somethingelse"));
	ASSERT_EQUAL_INT(array->len, 2);
	ASSERT_EQUAL_STR(*(char **)ft_array_get(array, 0), "test");
	ASSERT_EQUAL_STR(*(char **)ft_array_get(array, 1), "somethingelse");

	ft_array_free(array);
}

void test_ft_putchar()
{
	char *have = NULL;
	char want[3] = {'a', 0x00, 0xFF};
	int ret;

	ft_err_exit(start_fd_capture(1) == -1, "Failed to start fd capture!\n");
	ft_putchar('a');
	ft_putchar(0x00);
	ft_putchar(0xFF);
	ft_err_exit((ret = stop_fd_capture(1, &have)) == -1, "Failed to stop fd capture!\n");


	ASSERT(ret, ==, 3);
	ASSERT_NOBJ(memcmp, (char*)want, have, ret, == 0, ft_hexdump_fd);

	free(have);
}

void test_bigint_init()
{
	t_bigint num;

	bigint_init(num);

	// We cast num->sign because gcc doesn't let us do typeof() on a bitfield
	ASSERT((unsigned int)num->sign, ==, (unsigned int)BIGINT_POS);
	ASSERT(num->val[0], ==, (unsigned int)0);
	ASSERT(num->size, ==, (unsigned int)1);

	bigint_free(num);
}

void test_bigint_set_si()
{
	t_bigint num;

	bigint_init(num);

	bigint_set_si(num, BIGINT_MAX>>1);
	ASSERT((unsigned int)num->sign, ==, (unsigned int)BIGINT_POS);
	ASSERT(num->size, ==, (unsigned int)1);
	ASSERT(num->val[0], ==, BIGINT_MAX>>1);

	bigint_set_si(num, LONG_MIN);
	ASSERT((unsigned int)num->sign, ==, (unsigned int)BIGINT_NEG);
	ASSERT(num->size, ==, (unsigned int)1);
	ASSERT(num->val[0], ==, (unsigned long)LONG_MIN);

	bigint_set_si(num, -3);
	ASSERT((unsigned int)num->sign, ==, (unsigned int)BIGINT_NEG);
	ASSERT(num->size, ==, (unsigned int)1);
	ASSERT(num->val[0], ==, (unsigned long)3);

	bigint_free(num);
}

void test_bigint_set()
{
	t_bigint a;
	t_bigint b;

	bigint_init(a);
	bigint_init(b);

	bigint_set_si(b, INT_MAX);
	bigint_set(a, b);
	ASSERT((unsigned int)a->sign, ==, (unsigned int)b->sign);
	ASSERT(a->size, ==, b->size);
	ASSERT(a->val[0], ==, b->val[0]);

	bigint_set_si(b, INT_MIN);
	bigint_set(a, b);
	ASSERT((unsigned int)a->sign, ==, (unsigned int)b->sign);
	ASSERT(a->size, ==, b->size);
	ASSERT(a->val[0], ==, b->val[0]);

	bigint_free(a);
	bigint_free(b);
}

void test_bigint_set_ui()
{
	t_bigint num;

	bigint_init(num);

	bigint_set_ui(num, BIGINT_MAX);
	ASSERT((unsigned int)num->sign, ==, (unsigned int)BIGINT_POS);
	ASSERT(num->size, ==, (unsigned int)1);
	ASSERT(num->val[0], ==, BIGINT_MAX);

	bigint_free(num);
}

void test_bigint_abs()
{
	t_bigint abs;
	t_bigint num;

	bigint_init(abs);
	bigint_init(num);

	bigint_set_ui(num, BIGINT_MAX);
	bigint_abs(abs, num);
	ASSERT(abs->val[0], ==, num->val[0]);
	ASSERT((int)abs->sign, ==, (int)BIGINT_POS);

	bigint_abs(abs, num);
	num->sign = BIGINT_NEG;
	ASSERT(abs->val[0], ==, num->val[0]);
	ASSERT((int)abs->sign, ==, (int)BIGINT_POS);

	bigint_free(abs);
	bigint_free(num);
}

void test_bigint_cmp()
{
	t_bigint a;
	t_bigint b;

	bigint_init(a);
	bigint_init(b);

	bigint_set_ui(a, BIGINT_MAX);
	bigint_add_ui(a, a, 1);
	bigint_set_ui(b, 1);
	// op1 > op2
	ASSERT(bigint_cmp(a, b), ==, 1);
	// op1 < op2
	ASSERT(bigint_cmp(b, a), ==, -1);
	bigint_set(b, a);
	b->sign = BIGINT_NEG;
	// op1 > op2
	ASSERT(bigint_cmp(a, b), ==, 1);
	// op1 < op2
	ASSERT(bigint_cmp(b, a), ==, -1);

	// 1 == 1
	bigint_set_ui(a, 1);
	bigint_set_ui(b, 1);
	ASSERT(bigint_cmp(b, a), ==, 0);
	ASSERT(bigint_cmp(a, b), ==, 0);

	// 0 == 0
	bigint_set_ui(a, 0);
	bigint_set_ui(b, 0);
	ASSERT(bigint_cmp(a, b), ==, 0);

	bigint_free(a);
	bigint_free(b);
}

void test_bigint_cmpabs()
{
	t_bigint a;
	t_bigint b;

	bigint_init(a);
	bigint_init(b);

	bigint_set_ui(a, BIGINT_MAX);
	bigint_add_ui(a, a, 1);
	bigint_set_ui(b, 1);
	// op1 > op2
	ASSERT(bigint_cmpabs(a, b), ==, 1);
	// op1 < op2
	ASSERT(bigint_cmpabs(b, a), ==, -1);
	bigint_set(b, a);
	b->sign = BIGINT_NEG;
	// op1 == -op1
	ASSERT(bigint_cmpabs(a, b), ==, 0);
	// -op1 == op1
	ASSERT(bigint_cmpabs(b, a), ==, 0);

	// 1 == 1
	bigint_set_ui(a, 1);
	bigint_set_ui(b, 1);
	ASSERT(bigint_cmpabs(b, a), ==, 0);
	ASSERT(bigint_cmpabs(a, b), ==, 0);

	// 0 == 0
	bigint_set_ui(a, 0);
	bigint_set_ui(b, 0);
	ASSERT(bigint_cmpabs(a, b), ==, 0);

	bigint_free(a);
	bigint_free(b);
}

void test_bigint_cmp_si()
{
	t_bigint a;

	bigint_init(a);

	bigint_set_ui(a, INT_MAX - 1);
	// op1 > op2
	ASSERT(bigint_cmp_si(a, INT_MAX - 2), ==, 1);
	// op1 < op2
	ASSERT(bigint_cmp_si(a, INT_MAX), ==, -1);
	// op1 == op2
	ASSERT(bigint_cmp_si(a, INT_MAX - 1), ==, 0);

	// 1 == 1
	bigint_set_ui(a, 1);
	ASSERT(bigint_cmp_si(a, 1), ==, 0);

	// 0 == 0
	bigint_set_ui(a, 0);
	ASSERT(bigint_cmp_si(a, 0), ==, 0);

	bigint_free(a);
}

void test_bigint_add()
{
	t_bigint a;
	t_bigint b;
	t_bigint res;

	bigint_init(a);
	bigint_init(b);
	bigint_init(res);

	// a == 2..., b == 1...
	bigint_set_ui(b, BIGINT_MAX);
	bigint_add_ui(b, b, 1);
	bigint_set(a, b);
	a->val[1] = 2;

	// arg1 > arg2: arg1 + arg2
	a->sign = BIGINT_POS;
	b->sign = BIGINT_POS;
	bigint_add(res, a, b);
	ASSERT(res->val[1], ==, 3UL);
	ASSERT((int)res->sign, ==, BIGINT_POS);
	// arg1 > arg2: -arg1 + arg2
	a->sign = BIGINT_NEG;
	b->sign = BIGINT_POS;
	bigint_add(res, a, b);
	ASSERT(res->val[1], ==, 1UL);
	ASSERT((int)res->sign, ==, BIGINT_NEG);
	// arg1 > arg2: arg1 + -arg2
	a->sign = BIGINT_POS;
	b->sign = BIGINT_NEG;
	bigint_add(res, a, b);
	ASSERT(res->val[1], ==, 1UL);
	ASSERT((int)res->sign, ==, BIGINT_POS);
	// arg1 > arg2: -arg1 + -arg2
	a->sign = BIGINT_NEG;
	b->sign = BIGINT_NEG;
	bigint_add(res, a, b);
	ASSERT(res->val[1], ==, 3UL);
	ASSERT((int)res->sign, ==, BIGINT_NEG);

	// arg1 < arg2: arg1 + arg2
	b->sign = BIGINT_POS;
	a->sign = BIGINT_POS;
	bigint_add(res, b, a);
	ASSERT(res->val[1], ==, 3UL);
	ASSERT((int)res->sign, ==, BIGINT_POS);
	// arg1 < arg2: -arg1 + arg2
	b->sign = BIGINT_NEG;
	a->sign = BIGINT_POS;
	bigint_add(res, b, a);
	ASSERT(res->val[1], ==, 1UL);
	ASSERT((int)res->sign, ==, BIGINT_POS);
	// arg1 < arg2: arg1 + -arg2
	b->sign = BIGINT_POS;
	a->sign = BIGINT_NEG;
	bigint_add(res, b, a);
	ASSERT(res->val[1], ==, 1UL);
	ASSERT((int)res->sign, ==, BIGINT_NEG);
	// arg1 < arg2: -arg1 + -arg2
	b->sign = BIGINT_NEG;
	a->sign = BIGINT_NEG;
	bigint_add(res, b, a);
	ASSERT(res->val[1], ==, 3UL);
	ASSERT((int)res->sign, ==, BIGINT_NEG);

	bigint_set(b, a);
	// arg1 == arg2: arg1 + -arg2
	a->sign = BIGINT_POS;
	b->sign = BIGINT_NEG;
	bigint_add(res, a, b);
	ASSERT(bigint_cmp_si(res, 0), ==, 0);
	ASSERT((int)res->sign, ==, BIGINT_POS);
	// arg1 == arg2: -arg1 + arg2
	a->sign = BIGINT_NEG;
	b->sign = BIGINT_POS;
	bigint_add(res, a, b);
	ASSERT(bigint_cmp_si(res, 0), ==, 0);
	ASSERT((int)res->sign, ==, BIGINT_POS);

	bigint_free(a);
	bigint_free(b);
	bigint_free(res);
}

void test_bigint_sub()
{
	t_bigint a;
	t_bigint b;
	t_bigint res;

	bigint_init(a);
	bigint_init(b);
	bigint_init(res);

	// a == 2..., b == 1...
	bigint_set_ui(b, BIGINT_MAX);
	bigint_add_ui(b, b, 1);
	bigint_set(a, b);
	a->val[1] = 2;

	// arg1 > arg2: arg1 - arg2
	a->sign = BIGINT_POS;
	b->sign = BIGINT_POS;
	bigint_sub(res, a, b);
	ASSERT(res->val[1], ==, 1UL);
	ASSERT((int)res->sign, ==, BIGINT_POS);
	// arg1 > arg2: -arg1 - arg2
	a->sign = BIGINT_NEG;
	b->sign = BIGINT_POS;
	bigint_sub(res, a, b);
	ASSERT(res->val[1], ==, 3UL);
	ASSERT((int)res->sign, ==, BIGINT_NEG);
	// arg1 > arg2: arg1 - -arg2
	a->sign = BIGINT_POS;
	b->sign = BIGINT_NEG;
	bigint_sub(res, a, b);
	ASSERT(res->val[1], ==, 3UL);
	ASSERT((int)res->sign, ==, BIGINT_POS);
	// arg1 > arg2: -arg1 - -arg2
	a->sign = BIGINT_NEG;
	b->sign = BIGINT_NEG;
	bigint_sub(res, a, b);
	ASSERT(res->val[1], ==, 1UL);
	ASSERT((int)res->sign, ==, BIGINT_NEG);

	// arg1 < arg2: arg1 - arg2
	b->sign = BIGINT_POS;
	a->sign = BIGINT_POS;
	bigint_sub(res, b, a);
	ASSERT(res->val[1], ==, 1UL);
	ASSERT((int)res->sign, ==, BIGINT_NEG);
	// arg1 < arg2: -arg1 - arg2
	b->sign = BIGINT_NEG;
	a->sign = BIGINT_POS;
	bigint_sub(res, b, a);
	ASSERT(res->val[1], ==, 3UL);
	ASSERT((int)res->sign, ==, BIGINT_NEG);
	// arg1 < arg2: arg1 - -arg2
	b->sign = BIGINT_POS;
	a->sign = BIGINT_NEG;
	bigint_sub(res, b, a);
	ASSERT(res->val[1], ==, 3UL);
	ASSERT((int)res->sign, ==, BIGINT_POS);
	// arg1 < arg2: -arg1 - -arg2
	b->sign = BIGINT_NEG;
	a->sign = BIGINT_NEG;
	bigint_sub(res, b, a);
	ASSERT(res->val[1], ==, 1UL);
	ASSERT((int)res->sign, ==, BIGINT_POS);

	bigint_set(b, a);
	// arg1 == arg2: arg1 - arg2
	a->sign = BIGINT_POS;
	b->sign = BIGINT_POS;
	bigint_sub(res, a, b);
	ASSERT(bigint_cmp_si(res, 0), ==, 0);
	ASSERT((int)res->sign, ==, BIGINT_POS);
	// arg1 == arg2: -arg1 - -arg2
	a->sign = BIGINT_NEG;
	b->sign = BIGINT_NEG;
	bigint_sub(res, a, b);
	ASSERT(bigint_cmp_si(res, 0), ==, 0);
	ASSERT((int)res->sign, ==, BIGINT_POS);

	bigint_free(a);
	bigint_free(b);
	bigint_free(res);
}

void test_bigint_mul()
{
	t_bigint a;
	t_bigint b;
	t_bigint res;

	bigint_init(a);
	bigint_init(b);
	bigint_init(res);

	// a == 1..., b == 2
	bigint_set_ui(a, BIGINT_MAX);
	bigint_add_ui(a, a, 1);
	bigint_set_ui(b, 2);

	// arg1 x arg2
	a->sign = BIGINT_POS;
	b->sign = BIGINT_POS;
	bigint_mul(res, a, b);
	ASSERT(res->val[1], ==, 2UL);
	ASSERT((int)res->sign, ==, BIGINT_POS);
	bigint_mul(res, b, a);
	ASSERT(res->val[1], ==, 2UL);
	ASSERT((int)res->sign, ==, BIGINT_POS);
	// -arg1 x arg2
	a->sign = BIGINT_NEG;
	b->sign = BIGINT_POS;
	bigint_mul(res, a, b);
	ASSERT(res->val[1], ==, 2UL);
	ASSERT((int)res->sign, ==, BIGINT_NEG);
	bigint_mul(res, b, a);
	ASSERT(res->val[1], ==, 2UL);
	ASSERT((int)res->sign, ==, BIGINT_NEG);
	// arg1 x -arg2
	a->sign = BIGINT_POS;
	b->sign = BIGINT_NEG;
	bigint_mul(res, a, b);
	ASSERT(res->val[1], ==, 2UL);
	ASSERT((int)res->sign, ==, BIGINT_NEG);
	bigint_mul(res, b, a);
	ASSERT(res->val[1], ==, 2UL);
	ASSERT((int)res->sign, ==, BIGINT_NEG);
	// -arg1 x -arg2
	a->sign = BIGINT_NEG;
	b->sign = BIGINT_NEG;
	bigint_mul(res, a, b);
	ASSERT(res->val[1], ==, 2UL);
	ASSERT((int)res->sign, ==, BIGINT_POS);
	bigint_mul(res, b, a);
	ASSERT(res->val[1], ==, 2UL);
	ASSERT((int)res->sign, ==, BIGINT_POS);

	a->sign = BIGINT_POS;
	bigint_set_ui(b, 0);
	// arg1 x 0
	bigint_mul(res, a, b);
	ASSERT(bigint_cmp_si(res, 0), ==, 0);
	// 0 x arg1
	bigint_mul(res, b, a);
	ASSERT(bigint_cmp_si(res, 0), ==, 0);

	// res = res x res
	bigint_set_ui(res, 4);
	bigint_mul(res, res, res);
	ASSERT(res->val[0], ==, 16UL);
	ASSERT((int)res->sign, ==, BIGINT_POS);

	bigint_free(a);
	bigint_free(b);
	bigint_free(res);
}

void test_bigint_div()
{
	t_bigint a;
	t_bigint b;
	t_bigint q;
	t_bigint r;

	bigint_init(a);
	bigint_init(b);
	bigint_init(q);
	bigint_init(r);

	// a == 1..., b == 2
	bigint_set_ui(a, BIGINT_MAX);
	bigint_add_ui(a, a, 1);
	bigint_set_ui(b, 2);

	// arg1 / arg2
	a->sign = BIGINT_POS;
	b->sign = BIGINT_POS;
	bigint_div(q, r, a, b);
	ASSERT(q->val[0], ==, BIGINT_MAX/2);
	ASSERT(q->size, ==, 1U);
	ASSERT(bigint_cmp_si(q, BIGINT_MAX/2), ==, 0);
	ASSERT((int)q->sign, ==, BIGINT_POS);
	/* bigint_div(res, b, a); */
	/* ASSERT(res->val[1], ==, 2UL); */
	/* ASSERT((int)res->sign, ==, BIGINT_POS); */
	/* // -arg1 x arg2 */
	/* a->sign = BIGINT_NEG; */
	/* b->sign = BIGINT_POS; */
	/* bigint_div(res, a, b); */
	/* ASSERT(res->val[1], ==, 2UL); */
	/* ASSERT((int)res->sign, ==, BIGINT_NEG); */
	/* bigint_div(res, b, a); */
	/* ASSERT(res->val[1], ==, 2UL); */
	/* ASSERT((int)res->sign, ==, BIGINT_NEG); */
	/* // arg1 x -arg2 */
	/* a->sign = BIGINT_POS; */
	/* b->sign = BIGINT_NEG; */
	/* bigint_div(res, a, b); */
	/* ASSERT(res->val[1], ==, 2UL); */
	/* ASSERT((int)res->sign, ==, BIGINT_NEG); */
	/* bigint_div(res, b, a); */
	/* ASSERT(res->val[1], ==, 2UL); */
	/* ASSERT((int)res->sign, ==, BIGINT_NEG); */
	/* // -arg1 x -arg2 */
	/* a->sign = BIGINT_NEG; */
	/* b->sign = BIGINT_NEG; */
	/* bigint_div(res, a, b); */
	/* ASSERT(res->val[1], ==, 2UL); */
	/* ASSERT((int)res->sign, ==, BIGINT_POS); */
	/* bigint_div(res, b, a); */
	/* ASSERT(res->val[1], ==, 2UL); */
	/* ASSERT((int)res->sign, ==, BIGINT_POS); */

	/* a->sign = BIGINT_POS; */
	/* bigint_set_ui(b, 0); */
	/* // arg1 x 0 */
	/* bigint_div(res, a, b); */
	/* ASSERT(bigint_cmp_si(res, 0), ==, 0); */
	/* // 0 x arg1 */
	/* bigint_div(res, b, a); */
	/* ASSERT(bigint_cmp_si(res, 0), ==, 0); */

	/* // res = res x res */
	/* bigint_set_ui(res, 4); */
	/* bigint_div(res, res, res); */
	/* ASSERT(res->val[0], ==, 16UL); */
	/* ASSERT((int)res->sign, ==, BIGINT_POS); */

	bigint_free(a);
	bigint_free(b);
	bigint_free(q);
	bigint_free(r);
}

void test_bigint_get_bit()
{
	t_bigint a;

	bigint_init(a);

	// overflow val[0] to val[1]
	bigint_set_ui(a, BIGINT_MAX);
	bigint_shift_left(a, a);

	ASSERT(bigint_get_bit(a, 0), ==, 0);
	ASSERT(bigint_get_bit(a, 1), ==, 1);
	ASSERT(bigint_get_bit(a, BIGINT_VAL_NBIT), ==, 1);
	ASSERT(bigint_get_bit(a, BIGINT_VAL_NBIT + 1), ==, 0);

	bigint_free(a);
}

void test_bigint_set_bit()
{
	t_bigint a;

	bigint_init(a);

	bigint_set_ui(a, 0);

	bigint_set_bit(a, 0, 1);
	ASSERT(bigint_get_bit(a, 0), ==, 1);
	bigint_set_bit(a, BIGINT_VAL_NBIT - 1, 1);
	ASSERT(bigint_get_bit(a, BIGINT_VAL_NBIT - 1), ==, 1);

	bigint_set_ui(a, 0);
	bigint_realloc(a, 2);
	bigint_set_bit(a, BIGINT_VAL_NBIT, 1);
	ASSERT(bigint_get_bit(a, BIGINT_VAL_NBIT), ==, 1);

	bigint_free(a);
}

void test_bigint_shift_left()
{
	t_bigint a;

	bigint_init(a);

	bigint_set_ui(a, BIGINT_MAX);
	bigint_shift_left(a, a);
	ASSERT(a->size, ==, 2U);
	ASSERT(a->val[0], ==, BIGINT_MAX << 1);
	ASSERT(a->val[1], ==, 0b1U);
	bigint_shift_left(a, a);
	ASSERT(a->val[0], ==, BIGINT_MAX << 2);
	ASSERT(a->val[1], ==, 0b11U);

	// 0 << 1
	bigint_set_ui(a, 0);
	bigint_shift_left(a, a);
	ASSERT(a->size, ==, 1U);
	ASSERT(bigint_cmp_si(a, 0), ==, 0);

	bigint_free(a);
}

void test_bigint_num_bits()
{
	t_bigint a;

	bigint_init(a);

	ASSERT(bigint_num_bits(a), ==, 0U);
	bigint_set_si(a, -1);
	ASSERT(bigint_num_bits(a), ==, 1U);
	bigint_set_ui(a, BIGINT_MAX);
	ASSERT(bigint_num_bits(a), ==, BIGINT_VAL_NBIT);
	bigint_shift_left(a, a);
	ASSERT(bigint_num_bits(a), ==, BIGINT_VAL_NBIT + 1);
	bigint_shift_left(a, a);
	ASSERT(bigint_num_bits(a), ==, BIGINT_VAL_NBIT + 2);

	bigint_free(a);
}

void test_ft_lltostr()
{
	char *result;

	result = ft_lltostr(LLONG_MIN, "0123456789ABCDEF");
	ASSERT_OBJ(strcmp, result, "-8000000000000000", == 0, ft_putstr_fd);
	free(result);
	result = ft_lltostr(-1, "0123456789");
	ASSERT_OBJ(strcmp, result, "-1", == 0, ft_putstr_fd);
	free(result);
	result = ft_lltostr(-1, "0123456789ABCDEF");
	ASSERT_OBJ(strcmp, result, "-1", == 0, ft_putstr_fd);
	free(result);
	result = ft_lltostr(0, "0123456789ABCDEF");
	ASSERT_OBJ(strcmp, result, "0", == 0, ft_putstr_fd);
	free(result);
	result = ft_lltostr(1, "0123456789");
	ASSERT_OBJ(strcmp, result, "1", == 0, ft_putstr_fd);
	free(result);
	result = ft_lltostr(10, "0123456789");
	ASSERT_OBJ(strcmp, result, "10", == 0, ft_putstr_fd);
	free(result);
	result = ft_lltostr(15, "0123456789ABCDEF");
	ASSERT_OBJ(strcmp, result, "F", == 0, ft_putstr_fd);
	free(result);
	result = ft_lltostr(16, "0123456789ABCDEF");
	ASSERT_OBJ(strcmp, result, "10", == 0, ft_putstr_fd);
	free(result);
	result = ft_lltostr(LLONG_MAX, "0123456789ABCDEF");
	ASSERT_OBJ(strcmp, result, "7FFFFFFFFFFFFFFF", == 0, ft_putstr_fd);
	free(result);
}

void test_ft_ulltostr()
{
	char *result;

	result = ft_ulltostr(0, "0123456789ABCDEF");
	ASSERT_OBJ(strcmp, result, "0", == 0, ft_putstr_fd);
	free(result);
	result = ft_ulltostr(1, "0123456789");
	ASSERT_OBJ(strcmp, result, "1", == 0, ft_putstr_fd);
	free(result);
	result = ft_ulltostr(10, "0123456789");
	ASSERT_OBJ(strcmp, result, "10", == 0, ft_putstr_fd);
	free(result);
	result = ft_ulltostr(15, "0123456789ABCDEF");
	ASSERT_OBJ(strcmp, result, "F", == 0, ft_putstr_fd);
	free(result);
	result = ft_ulltostr(16, "0123456789ABCDEF");
	ASSERT_OBJ(strcmp, result, "10", == 0, ft_putstr_fd);
	free(result);
	result = ft_ulltostr(ULLONG_MAX, "0123456789ABCDEF");
	ASSERT_OBJ(strcmp, result, "FFFFFFFFFFFFFFFF", == 0, ft_putstr_fd);
	free(result);
}

void test_ft_num_digits_ll()
{
	ASSERT(ft_num_digits_ll(LLONG_MIN, 10), ==, 19U);
	ASSERT(ft_num_digits_ll(LLONG_MIN, 16), ==, 16U);
	ASSERT(ft_num_digits_ll(-10, 10), ==, 2U);
	ASSERT(ft_num_digits_ll(-16, 16), ==, 2U);
	ASSERT(ft_num_digits_ll(-1, 10), ==, 1U);
	ASSERT(ft_num_digits_ll(0, 10), ==, 1U);
	ASSERT(ft_num_digits_ll(1, 10), ==, 1U);
	ASSERT(ft_num_digits_ll(10, 10), ==, 2U);
	ASSERT(ft_num_digits_ll(16, 16), ==, 2U);
	ASSERT(ft_num_digits_ll(LLONG_MAX, 10), ==, 19U);
	ASSERT(ft_num_digits_ll(LLONG_MAX, 16), ==, 16U);
}

void test_ft_num_digits_ull()
{
	ASSERT(ft_num_digits_ull(0, 10), ==, 1U);
	ASSERT(ft_num_digits_ull(1, 10), ==, 1U);
	ASSERT(ft_num_digits_ull(10, 10), ==, 2U);
	ASSERT(ft_num_digits_ull(16, 16), ==, 2U);
	ASSERT(ft_num_digits_ull(LLONG_MAX, 10), ==, 19U);
	ASSERT(ft_num_digits_ull(LLONG_MAX, 16), ==, 16U);
	ASSERT(ft_num_digits_ull(ULLONG_MAX, 10), ==, 20U);
	ASSERT(ft_num_digits_ull(ULLONG_MAX, 16), ==, 16U);
}

void test_ft_ltrim()
{
	ASSERT(strcmp(ft_ltrim("", ""), ""), ==, 0);
	ASSERT(strcmp(ft_ltrim("abc", ""), "abc"), ==, 0);

	ASSERT(strcmp(ft_ltrim("", " \t"), ""), ==, 0);
	ASSERT(strcmp(ft_ltrim(" ", " \t"), ""), ==, 0);
	ASSERT(strcmp(ft_ltrim("\t", " \t"), ""), ==, 0);
	ASSERT(strcmp(ft_ltrim(" \t", " \t"), ""), ==, 0);
	ASSERT(strcmp(ft_ltrim("\t ", " \t"), ""), ==, 0);

	ASSERT(strcmp(ft_ltrim("abc", " \t"), "abc"), ==, 0);
	ASSERT(strcmp(ft_ltrim(" abc", " \t"), "abc"), ==, 0);
	ASSERT(strcmp(ft_ltrim("  abc", " \t"), "abc"), ==, 0);
	ASSERT(strcmp(ft_ltrim("\tabc", " \t"), "abc"), ==, 0);
	ASSERT(strcmp(ft_ltrim("\t abc", " \t"), "abc"), ==, 0);
	ASSERT(strcmp(ft_ltrim(" \tabc", " \t"), "abc"), ==, 0);
	ASSERT(strcmp(ft_ltrim(" \t abc", " \t"), "abc"), ==, 0);
	ASSERT(strcmp(ft_ltrim("\t \tabc", " \t"), "abc"), ==, 0);
	ASSERT(strcmp(ft_ltrim("a b c ", " \t"), "a b c "), ==, 0);
}

void test_ft_rtrim()
{
	char *str;

	str = strdup("");
	ASSERT(strcmp(ft_rtrim(str, " \t"), ""), ==, 0); free(str);
	str = strdup("abc");
	ASSERT(strcmp(ft_rtrim(str, " \t"), "abc"), ==, 0); free(str);

	str = strdup(" ");
	ASSERT(strcmp(ft_rtrim(str, " \t"), ""), ==, 0); free(str);
	str = strdup("\t");
	ASSERT(strcmp(ft_rtrim(str, " \t"), ""), ==, 0); free(str);
	str = strdup(" \t");
	ASSERT(strcmp(ft_rtrim(str, " \t"), ""), ==, 0); free(str);
	str = strdup("\t ");
	ASSERT(strcmp(ft_rtrim(str, " \t"), ""), ==, 0); free(str);

	str = strdup("abc");
	ASSERT(strcmp(ft_rtrim(str, " \t"), "abc"), ==, 0); free(str);
	str = strdup("abc ");
	ASSERT(strcmp(ft_rtrim(str, " \t"), "abc"), ==, 0); free(str);
	str = strdup("abc  ");
	ASSERT(strcmp(ft_rtrim(str, " \t"), "abc"), ==, 0); free(str);
	str = strdup("abc\t");
	ASSERT(strcmp(ft_rtrim(str, " \t"), "abc"), ==, 0); free(str);
	str = strdup("abc\t ");
	ASSERT(strcmp(ft_rtrim(str, " \t"), "abc"), ==, 0); free(str);
	str = strdup("abc \t");
	ASSERT(strcmp(ft_rtrim(str, " \t"), "abc"), ==, 0); free(str);
	str = strdup("abc \t ");
	ASSERT(strcmp(ft_rtrim(str, " \t"), "abc"), ==, 0); free(str);
	str = strdup("abc\t \t");
	ASSERT(strcmp(ft_rtrim(str, " \t"), "abc"), ==, 0); free(str);
	str = strdup(" a b c");
	ASSERT(strcmp(ft_rtrim(str, " \t"), " a b c"), ==, 0); free(str);
}

void test_ft_trim()
{
	char *str;

	str = strdup("");
	ASSERT(strcmp(ft_trim(str, " \t"), ""), ==, 0); free(str);
	str = strdup("abc");
	ASSERT(strcmp(ft_trim(str, " \t"), "abc"), ==, 0); free(str);

	str = strdup(" ");
	ASSERT(strcmp(ft_trim(str, " \t"), ""), ==, 0); free(str);
	str = strdup("\t");
	ASSERT(strcmp(ft_trim(str, " \t"), ""), ==, 0); free(str);
	str = strdup(" \t");
	ASSERT(strcmp(ft_trim(str, " \t"), ""), ==, 0); free(str);
	str = strdup("\t ");
	ASSERT(strcmp(ft_trim(str, " \t"), ""), ==, 0); free(str);

	str = strdup("abc");
	ASSERT(strcmp(ft_trim(str, " \t"), "abc"), ==, 0); free(str);
	str = strdup(" abc ");
	ASSERT(strcmp(ft_trim(str, " \t"), "abc"), ==, 0); free(str);
	str = strdup("  abc  ");
	ASSERT(strcmp(ft_trim(str, " \t"), "abc"), ==, 0); free(str);
	str = strdup("\tabc\t");
	ASSERT(strcmp(ft_trim(str, " \t"), "abc"), ==, 0); free(str);
	str = strdup(" \tabc\t ");
	ASSERT(strcmp(ft_trim(str, " \t"), "abc"), ==, 0); free(str);
	str = strdup("\t abc \t");
	ASSERT(strcmp(ft_trim(str, " \t"), "abc"), ==, 0); free(str);
	str = strdup(" \t abc \t ");
	ASSERT(strcmp(ft_trim(str, " \t"), "abc"), ==, 0); free(str);
	str = strdup("\t \tabc\t \t");
	ASSERT(strcmp(ft_trim(str, " \t"), "abc"), ==, 0); free(str);
	str = strdup(" a b c ");
	ASSERT(strcmp(ft_trim(str, " \t"), "a b c"), ==, 0); free(str);
}

void test_str_to_bstr()
{
	t_bstr result;
	char *str;

	str = "abc";
	result = str_to_bstr(str);
	ASSERT(result.str, ==, str);
	ASSERT(result.len, ==, 3U);

	str = "";
	result = str_to_bstr(str);
	ASSERT(result.str, ==, str);
	ASSERT(result.len, ==, 0U);
}

void test_bstr_cmp()
{
	t_bstr s1;
	t_bstr s2;

	// equal
	s1 = str_to_bstr("bcd");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_cmp(s1, s2), ==, 0);

	// before because smaller
	s1 = str_to_bstr("bc");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_cmp(s1, s2), <, 0);

	// smaller and before
	s1 = str_to_bstr("bb");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_cmp(s1, s2), <, 0);

	// smaller and after
	s1 = str_to_bstr("bd");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_cmp(s1, s2), >, 0);

	// same length but before
	s1 = str_to_bstr("bcc");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_cmp(s1, s2), <, 0);

	// same length but after
	s1 = str_to_bstr("bce");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_cmp(s1, s2), >, 0);

	// after because longer
	s1 = str_to_bstr("bcda");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_cmp(s1, s2), >, 0);

	// longer and before
	s1 = str_to_bstr("bcca");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_cmp(s1, s2), <, 0);

	// longer and after
	s1 = str_to_bstr("bcea");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_cmp(s1, s2), >, 0);
}

void test_bstr_ncmp()
{
	t_bstr s1;
	t_bstr s2;

	// equal
	s1 = str_to_bstr("bcd");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_ncmp(s1, s2, 3), ==, 0);

	// equal on n chars
	s1 = str_to_bstr("bcd");
	s2 = str_to_bstr("bde");
	ASSERT(bstr_ncmp(s1, s2, 1), ==, 0);

	// equal on n chars
	s1 = str_to_bstr("bcd");
	s2 = str_to_bstr("bce");
	ASSERT(bstr_ncmp(s1, s2, 2), ==, 0);

	// equal and n longer than the strings
	s1 = str_to_bstr("bcd");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_ncmp(s1, s2, 5), ==, 0);

	// equal and n smaller than s2
	s1 = str_to_bstr("b");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_ncmp(s1, s2, 1), ==, 0);

	// before on n chars
	s1 = str_to_bstr("bcd");
	s2 = str_to_bstr("bde");
	ASSERT(bstr_ncmp(s1, s2, 2), <, 0);

	// after on n chars
	s1 = str_to_bstr("bde");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_ncmp(s1, s2, 2), >, 0);

	// before because smaller
	s1 = str_to_bstr("bc");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_ncmp(s1, s2, 3), <, 0);

	// smaller and before
	s1 = str_to_bstr("bb");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_ncmp(s1, s2, 3), <, 0);

	// smaller and after
	s1 = str_to_bstr("bd");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_ncmp(s1, s2, 3), >, 0);

	// same length but before
	s1 = str_to_bstr("bcc");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_ncmp(s1, s2, 3), <, 0);

	// same length but after
	s1 = str_to_bstr("bce");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_ncmp(s1, s2, 3), >, 0);

	// after because longer
	s1 = str_to_bstr("bcda");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_ncmp(s1, s2, 4), >, 0);

	// longer and before
	s1 = str_to_bstr("bcca");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_ncmp(s1, s2, 4), <, 0);

	// longer and after
	s1 = str_to_bstr("bcea");
	s2 = str_to_bstr("bcd");
	ASSERT(bstr_ncmp(s1, s2, 4), >, 0);
}

void test_bstr_read_until()
{
	t_bstr test;
	t_bstr new;
	char *str;

	// Read until a char
	str = "abc";
	test = str_to_bstr(str);
	new = bstr_read_until(&test, "c");
	ASSERT(new.str, ==, str);
	ASSERT(new.len, ==, 2U);
	ASSERT(test.str, ==, str + 2);
	ASSERT(test.len, ==, 1U);

	// Read until two chars
	str = "abc";
	test = str_to_bstr(str);
	new = bstr_read_until(&test, "cb");
	ASSERT(new.str, ==, str);
	ASSERT(new.len, ==, 1U);
	ASSERT(test.str, ==, str + 1);
	ASSERT(test.len, ==, 2U);

	// Read the whole bstr with an empty charset
	str = "abc";
	test = str_to_bstr(str);
	new = bstr_read_until(&test, "");
	ASSERT(new.str, ==, str);
	ASSERT(new.len, ==, 3U);
	ASSERT(test.str, ==, str + 3);
	ASSERT(test.len, ==, 0U);

	// Read the whole bstr with a charset that isn't in the bstr
	str = "abc";
	test = str_to_bstr(str);
	new = bstr_read_until(&test, "d");
	ASSERT(new.str, ==, str);
	ASSERT(new.len, ==, 3U);
	ASSERT(test.str, ==, str + 3);
	ASSERT(test.len, ==, 0U);

	// Read until the first char
	str = "abc";
	test = str_to_bstr(str);
	new = bstr_read_until(&test, "a");
	ASSERT(new.str, ==, str);
	ASSERT(new.len, ==, 0U);
	ASSERT(test.str, ==, str);
	ASSERT(test.len, ==, 3U);
}

void test_bstr_skip_char()
{
	t_bstr test;
	char *str;

	// Read character in bstr
	str = "abc";
	test = str_to_bstr(str);
	ASSERT(bstr_skip_char(&test, 'a'), ==, 1U);
	ASSERT(test.str, ==, str + 1);
	ASSERT(test.len, ==, 2U);

	// Read character not in bstr
	str = "abc";
	test = str_to_bstr(str);
	ASSERT(bstr_skip_char(&test, 'z'), ==, 0U);
	ASSERT(test.str, ==, str);
	ASSERT(test.len, ==, 3U);

	// bstr is empty
	str = "";
	test = str_to_bstr(str);
	ASSERT(bstr_skip_char(&test, 'a'), ==, 0U);
	ASSERT(test.str, ==, str);
	ASSERT(test.len, ==, 0U);
}

void test_bstr_skip_chars()
{
	t_bstr test;
	char *str;

	// Read the whole bstr
	str = "abc";
	test = str_to_bstr(str);
	ASSERT(bstr_skip_chars(&test, "abc"), ==, 3U);
	ASSERT(test.str, ==, str + 3);
	ASSERT(test.len, ==, 0U);

	// Read part of the bstr
	str = "abc";
	test = str_to_bstr(str);
	ASSERT(bstr_skip_chars(&test, "ba"), ==, 2U);
	ASSERT(test.str, ==, str + 2);
	ASSERT(test.len, ==, 1U);

	// Read none of the bstr
	str = "abc";
	test = str_to_bstr(str);
	ASSERT(bstr_skip_chars(&test, "z"), ==, 0U);
	ASSERT(test.str, ==, str);
	ASSERT(test.len, ==, 3U);

	// Read from an empty bstr
	str = "";
	test = str_to_bstr(str);
	ASSERT(bstr_skip_chars(&test, "z"), ==, 0U);
	ASSERT(test.str, ==, str);
	ASSERT(test.len, ==, 0U);

	// Read with an empty charset
	str = "abc";
	test = str_to_bstr(str);
	ASSERT(bstr_skip_chars(&test, ""), ==, 0U);
	ASSERT(test.str, ==, str);
	ASSERT(test.len, ==, 3U);
}

void test_bstr_ltrim()
{
	t_bstr in;
	t_bstr out;
	t_bstr want;

	// 1 char once
	in = str_to_bstr(" abc");
	out = bstr_ltrim(in, " ");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// 1 char leading and trailing
	in = str_to_bstr(" abc ");
	out = bstr_ltrim(in, " ");
	want = str_to_bstr("abc ");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// 1 char twice
	in = str_to_bstr("  abc");
	out = bstr_ltrim(in, " ");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// 2 chars once in order
	in = str_to_bstr(" \tabc");
	out = bstr_ltrim(in, " \t");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// 2 chars once out of order
	in = str_to_bstr("\t abc");
	out = bstr_ltrim(in, " \t");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// multiple chars mixed
	in = str_to_bstr(" \t \t abc");
	out = bstr_ltrim(in, "\t ");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);
}

void test_bstr_rtrim()
{
	t_bstr in;
	t_bstr out;
	t_bstr want;

	// 1 char once
	in = str_to_bstr("abc ");
	out = bstr_rtrim(in, " ");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// 1 char leading and trailing
	in = str_to_bstr(" abc ");
	out = bstr_rtrim(in, " ");
	want = str_to_bstr(" abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// 1 char twice
	in = str_to_bstr("abc  ");
	out = bstr_rtrim(in, " ");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// 2 chars once in order
	in = str_to_bstr("abc \t");
	out = bstr_rtrim(in, " \t");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// 2 chars once out of order
	in = str_to_bstr("abc\t ");
	out = bstr_rtrim(in, " \t");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// multiple chars mixed
	in = str_to_bstr("abc \t \t ");
	out = bstr_rtrim(in, "\t ");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);
}

void test_bstr_trim()
{
	t_bstr in;
	t_bstr out;
	t_bstr want;

	// Left only
	// 1 char once
	in = str_to_bstr(" abc");
	out = bstr_trim(in, " ");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// 1 char twice
	in = str_to_bstr("  abc");
	out = bstr_trim(in, " ");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// 2 chars once in order
	in = str_to_bstr(" \tabc");
	out = bstr_trim(in, " \t");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// 2 chars once out of order
	in = str_to_bstr("\t abc");
	out = bstr_trim(in, " \t");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// multiple chars mixed
	in = str_to_bstr(" \t \t abc");
	out = bstr_trim(in, "\t ");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);


	// Right only
	// 1 char once
	in = str_to_bstr("abc ");
	out = bstr_trim(in, " ");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// 1 char twice
	in = str_to_bstr("abc  ");
	out = bstr_trim(in, " ");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// 2 chars once in order
	in = str_to_bstr("abc \t");
	out = bstr_trim(in, " \t");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// 2 chars once out of order
	in = str_to_bstr("abc\t ");
	out = bstr_trim(in, " \t");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// multiple chars mixed
	in = str_to_bstr("abc \t \t ");
	out = bstr_trim(in, "\t ");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);


	// Both
	// 1 char once
	in = str_to_bstr(" abc ");
	out = bstr_trim(in, " ");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// 1 char twice
	in = str_to_bstr("  abc  ");
	out = bstr_trim(in, " ");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// 2 chars once in order
	in = str_to_bstr(" \tabc \t");
	out = bstr_trim(in, " \t");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// 2 chars once out of order
	in = str_to_bstr("\t abc\t ");
	out = bstr_trim(in, " \t");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);

	// multiple chars mixed
	in = str_to_bstr(" \t \t abc \t \t ");
	out = bstr_trim(in, "\t ");
	want = str_to_bstr("abc");
	ASSERT(bstr_cmp(out, want), ==, 0);
}

void test_ft_betoh16()
{
	// This test assumes a little-endian host order
	ASSERT(ft_betoh16(0x0102), ==, 0x0201U);
	ASSERT(ft_betoh16(0xFFEE), ==, 0xEEFFU);
}

void test_ft_betoh32()
{
	// This test assumes a little-endian host order
	ASSERT(ft_betoh32(0x01020304), ==, 0x04030201U);
	ASSERT(ft_betoh32(0xFFEEDDCC), ==, 0xCCDDEEFFU);
}

void test_ft_betoh64()
{
	// This test assumes a little-endian host order
	ASSERT(ft_betoh64(0x0102030405060708), ==, 0x0807060504030201ULL);
	ASSERT(ft_betoh64(0xFFEEDDCCBBAA0908), ==, 0x0809AABBCCDDEEFFULL);
}

void test_ft_htobe16()
{
	// This test assumes a little-endian host order
	ASSERT(ft_htobe16(0x0102), ==, 0x0201U);
	ASSERT(ft_htobe16(0xFFEE), ==, 0xEEFFU);
}

void test_ft_htobe32()
{
	// This test assumes a little-endian host order
	ASSERT(ft_htobe32(0x01020304), ==, 0x04030201U);
	ASSERT(ft_htobe32(0xFFEEDDCC), ==, 0xCCDDEEFFU);
}

void test_ft_htobe64()
{
	// This test assumes a little-endian host order
	ASSERT(ft_htobe64(0x0102030405060708), ==, 0x0807060504030201U);
	ASSERT(ft_htobe64(0xFFEEDDCCBBAA0908), ==, 0x0809AABBCCDDEEFFU);
}

int		main()
{
	/*** Old Framework Tests ***/
	test_ft_atoi();
	test_ft_charcasecmp();
	test_ft_count_words();
	test_ft_count_words_c();
	test_ft_incharset();
	test_ft_isspace();
	test_ft_itoa();
	test_ft_stpncpy();
	test_ft_strcasecmp();
	test_ft_strncasecmp();
	test_ft_strcasestr();
	test_ft_strlcpy();
	test_ft_strndup();
	test_ft_strnlen();
	test_ft_strpbrk();
	test_ft_strsplit();
	test_ft_strtol();
	test_ft_strspn();
	test_ft_strsub();
	test_ft_strcspn();

	test_ft_lstissorted();
	test_ft_lstfree();
	test_ft_lstmap();
	test_ft_lstmergesort();
	test_ft_lstpush();

	test_ft_tab_push_ptr();

	test_ft_strrev();
	test_ft_num_digits();

	test_ft_pow();

	test_ft_swap();
	test_ft_issorted();
	test_ft_qsort();

	test_ft_bstrdup();
	test_ft_bstrtrunc();

	test_ft_array_new();
	test_ft_array_push();

	/* TODO */
	/* test_ft_gnl(); */
	/* test_ft_read_all(); */
	/* test_ft_realloc(); */

	/*** New Framework Tests ***/
	RUN_TEST(test_ft_putchar);

	RUN_TEST(test_bigint_init);
	/* RUN_TEST(test_bigint_fix_size); */

	RUN_TEST(test_bigint_set);
	RUN_TEST(test_bigint_set_si);
	RUN_TEST(test_bigint_set_ui);
	RUN_TEST(test_bigint_abs);

	RUN_TEST(test_bigint_cmp);
	RUN_TEST(test_bigint_cmpabs);
	RUN_TEST(test_bigint_cmp_si);

	RUN_TEST(test_bigint_add);
	RUN_TEST(test_bigint_sub);

	RUN_TEST(test_bigint_mul);

	/* RUN_TEST(test_bigint_div); */

	/* RUN_TEST(test_bigint_get_bit); */
	/* RUN_TEST(test_bigint_set_bit); */
	/* RUN_TEST(test_bigint_shift_left); */
	/* RUN_TEST(test_bigint_num_bits); */

	RUN_TEST(test_ft_lltostr);
	RUN_TEST(test_ft_ulltostr);

	RUN_TEST(test_ft_num_digits_ll);
	RUN_TEST(test_ft_num_digits_ull);

	RUN_TEST(test_ft_ltrim);
	RUN_TEST(test_ft_rtrim);
	RUN_TEST(test_ft_trim);

	RUN_TEST(test_str_to_bstr);
	RUN_TEST(test_bstr_cmp);
	RUN_TEST(test_bstr_ncmp);

	RUN_TEST(test_bstr_read_until);
	RUN_TEST(test_bstr_skip_char);
	RUN_TEST(test_bstr_skip_chars);

	RUN_TEST(test_bstr_ltrim);
	RUN_TEST(test_bstr_rtrim);
	RUN_TEST(test_bstr_trim);

	RUN_TEST(test_ft_betoh16);
	RUN_TEST(test_ft_betoh32);
	RUN_TEST(test_ft_betoh64);
	RUN_TEST(test_ft_htobe16);
	RUN_TEST(test_ft_htobe32);
	RUN_TEST(test_ft_htobe64);
}
