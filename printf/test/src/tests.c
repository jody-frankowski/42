#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libft.h"
#include "libprintf.h"
#include "libunit.h"

void test_apppend_nchar()
{
	char *test = malloc(20);

	test[0] = '\0';
	append_nchar(test, 'a', 3);
	ASSERT_OBJ(strcmp, test, "aaa", == 0, ft_putstr_fd);
	append_nchar(test, 'b', 3);
	ASSERT_OBJ(strcmp, test, "aaabbb", == 0, ft_putstr_fd);
	append_nchar(test, 'c', -1);
	ASSERT_OBJ(strcmp, test, "aaabbb", == 0, ft_putstr_fd);

	free(test);
}

void test_prepend_nchar()
{
	char *test = malloc(20);

	test[0] = '\0';
	prepend_nchar(test, 'a', 3);
	ASSERT_OBJ(strcmp, test, "aaa", == 0, ft_putstr_fd);
	prepend_nchar(test, 'b', 3);
	ASSERT_OBJ(strcmp, test, "bbbaaa", == 0, ft_putstr_fd);
	prepend_nchar(test, 'c', -1);
	ASSERT_OBJ(strcmp, test, "bbbaaa", == 0, ft_putstr_fd);

	free(test);
}

void test_parse_conversion()
{
	t_conv conv;
	const char *format;
	const char *new_format;

	format = strdup("%");
	new_format = format;
	conv = parse_conversion(&new_format);
	ASSERT(new_format, ==, format + strlen(format));
	ASSERT((char)conv.specifier, ==, '%');
	free((char*)format);

	// Complete example
	format = strdup("#0- +50.-40hd");
	new_format = format;
	conv = parse_conversion(&new_format);
	ASSERT(new_format, ==, format + strlen(format));
	ASSERT((int)conv.hash_flag, ==, 1);
	ASSERT((int)conv.zero_flag, ==, 1);
	ASSERT((int)conv.minus_flag, ==, 1);
	ASSERT((int)conv.space_flag, ==, 1);
	ASSERT((int)conv.plus_flag, ==, 1);
	ASSERT(conv.field_width, ==, 50U);
	ASSERT(conv.precision, ==, -40);
	ASSERT((int)conv.precision_flag, ==, 0);
	ASSERT((int)conv.length_modifier_flag, ==, 1);
	ASSERT((int)conv.length_modifier, ==, H);
	ASSERT((char)conv.specifier, ==, 'd');
	free((char*)format);

	// random order
	format = strdup("+ -0#50.-40lld");
	new_format = format;
	conv = parse_conversion(&new_format);
	ASSERT(new_format, ==, format + strlen(format));
	ASSERT((int)conv.hash_flag, ==, 1);
	ASSERT((int)conv.zero_flag, ==, 1);
	ASSERT((int)conv.minus_flag, ==, 1);
	ASSERT((int)conv.space_flag, ==, 1);
	ASSERT((int)conv.plus_flag, ==, 1);
	ASSERT(conv.field_width, ==, 50U);
	ASSERT(conv.precision, ==, -40);
	ASSERT((int)conv.precision_flag, ==, 0);
	ASSERT((int)conv.length_modifier_flag, ==, 1);
	ASSERT((int)conv.length_modifier, ==, LL);
	ASSERT((char)conv.specifier, ==, 'd');
	free((char*)format);

	// Empty precision
	format = strdup(".x");
	new_format = format;
	conv = parse_conversion(&new_format);
	ASSERT(new_format, ==, format + strlen(format));
	ASSERT(conv.precision, ==, 0);
	ASSERT((int)conv.precision_flag, ==, 1);
	ASSERT((char)conv.specifier, ==, 'x');
	free((char*)format);
}


// We use a macro for this because otherwise, the ASSERT() macros would print
// the same line number every time (the one where they would get called in a
// normal function)
#define COMPARE_PRINTF(format, ...)  \
do { \
	char original_str[1000]; \
	char my_str[1000]; \
	char *original_output; \
	char *my_output; \
	int original_return; \
	int my_return; \
	int original_output_length; \
	int my_output_length; \
\
	/* sprintf test */ \
	original_return = sprintf(original_str, format, ##__VA_ARGS__); \
	my_return = ft_sprintf(my_str, format, ##__VA_ARGS__); \
	ASSERT(original_return, ==, my_return); \
	ASSERT_NOBJ(memcmp, (char*)original_str, (char*)my_str, original_return, == 0, write); \
\
	/* printf test */ \
	original_output = NULL; \
	my_output = NULL; \
\
	if (start_fd_capture(1) == -1) \
	{ \
		fprintf(stderr, "start_fd_capture@%s:%d: %s", __FILE__, __LINE__, strerror(errno)); \
		exit(-1); \
	} \
	original_return = printf(format, ##__VA_ARGS__); \
	if ((original_output_length = stop_fd_capture(1, &original_output)) == -1) \
	{ \
		fprintf(stderr, "stop_fd_capture@%s:%d: %s", __FILE__, __LINE__, strerror(errno)); \
		exit(-1); \
	} \
\
	if (start_fd_capture(1) == -1) \
	{ \
		fprintf(stderr, "start_fd_capture@%s:%d: %s", __FILE__, __LINE__, strerror(errno)); \
		exit(-1); \
	} \
	my_return = ft_printf(format, ##__VA_ARGS__); \
	if ((my_output_length = stop_fd_capture(1, &my_output)) == -1) \
	{ \
		fprintf(stderr, "stop_fd_capture@%s:%d: %s", __FILE__, __LINE__, strerror(errno)); \
		exit(-1); \
	} \
\
	ASSERT(original_return, ==, my_return); \
	ASSERT(original_output_length, ==, my_output_length); \
	ASSERT_NOBJ(memcmp, original_output, my_output, original_return, == 0, write); \
	free(original_output); \
	free(my_output); \
} while(0);

void test_printf_and_sprintf()
{
	// %%
	COMPARE_PRINTF("|%%%%|%%|%%|");
	// with field width
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wformat"
	#if __APPLE__
	COMPARE_PRINTF("|%1%|%2%|");
	#endif
	#pragma GCC diagnostic pop

	// c
	COMPARE_PRINTF("|%c|%c|%c|%c|", 1, 127, 128, 255);
	// with 0
	COMPARE_PRINTF("|%c|", 0);
	// with field width
	//      smaller, equal and larger than the value
	COMPARE_PRINTF("|%1c|%2c|%3c|", 'a', 'a', 'a');
	//      with - flag
	COMPARE_PRINTF("|%-5c|", 'a');

	// s
	COMPARE_PRINTF("|%s|", "ab");
	#if __GNUC
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wformat-overflow"
	#endif
	#if __APPLE__
	// with NULL
	COMPARE_PRINTF("|%1.1s|", (char*)NULL);
	#endif
	#if __GNUC
	#pragma GCC diagnostic pop
	#endif
	// with empty string
	COMPARE_PRINTF("%s", "");
	// with precision
	//      smaller, equal and larger than the value
	COMPARE_PRINTF("|%.1s|%.2s|%.3s|%.4s|", "ab", "ab", "ab", "ab");
	//      empty
	COMPARE_PRINTF("|%.s|", "ab");
	//      0
	COMPARE_PRINTF("|%.0s|", "ab");
	//      negative
	/* COMPARE_PRINTF("|%.-3s|", "ab"); */
	// with field width
	//      smaller, equal and larger than the value
	COMPARE_PRINTF("|%1s|%2s|%3s|%4s|", "ab", "ab", "ab", "ab");
	//      with 0 flag
	/* COMPARE_PRINTF("|%09s|", "ab"); */
	//      with - flag
	COMPARE_PRINTF("|%-1s|%-2s|%-3s|%-4s|", "ab", "ab", "ab", "ab");

	// p
	COMPARE_PRINTF("|%p|", exit);
	#if __APPLE__
	// with NULL
	COMPARE_PRINTF("|%p|", NULL);
	#endif
	// with 1
	COMPARE_PRINTF("|%p|", (void*)1);
	// With the longest values possible
	COMPARE_PRINTF("|%p|%p|", (void*)LLONG_MIN, (void*)ULLONG_MAX);
	// with field width
	COMPARE_PRINTF("|%12p|%13p|%14p|%15p|%16p|", exit, exit, exit, exit, exit);
	//      with 0 flag
	/* COMPARE_PRINTF("|%09p|", printf); */
	//      with - flag
	COMPARE_PRINTF("|%-1p|%-2p|%-3p|%-4p|", exit, exit, exit, exit);

	// d, i, o, u, x, X
	// with 0
	COMPARE_PRINTF("|%d|", 0);
	COMPARE_PRINTF("|%o|", 0);
	COMPARE_PRINTF("|%u|", 0);
	COMPARE_PRINTF("|%x|", 0);
	//      and precision 0
	COMPARE_PRINTF("|%.0d|%.d|", 0, 0);
	COMPARE_PRINTF("|%.0o|%.o|", 0, 0);
	COMPARE_PRINTF("|%.0u|%.u|", 0, 0);
	COMPARE_PRINTF("|%.0x|%.x|", 0, 0);
	//          and field width
	COMPARE_PRINTF("|%1.0d|%1.d|%2.0d|%2.d|", 0, 0, 0, 0);
	COMPARE_PRINTF("|%1.0o|%1.o|%2.0o|%2.o|", 0, 0, 0, 0);
	COMPARE_PRINTF("|%1.0u|%1.u|%2.0u|%2.u|", 0, 0, 0, 0);
	COMPARE_PRINTF("|%1.0x|%1.x|%2.0x|%2.x|", 0, 0, 0, 0);
	// with 1
	COMPARE_PRINTF("|%d|%d|", -1, 1);
	COMPARE_PRINTF("|%o|", 1);
	COMPARE_PRINTF("|%u|", 1);
	COMPARE_PRINTF("|%x|", 1);
	// with base border values
	COMPARE_PRINTF("|%d|%d|%d|%d|%d|%d|", -11, -10, -9, 9, 10, 11);
	COMPARE_PRINTF("|%o|%o|%o|", 7, 8, 9);
	COMPARE_PRINTF("|%u|%u|%u|", 9, 10, 11);
	COMPARE_PRINTF("|%x|%x|%x|", 15, 16, 17);
	// With the longest values possible
	COMPARE_PRINTF("|%lld|%lld|", LLONG_MIN, LLONG_MAX);
	COMPARE_PRINTF("|%llo|", ULLONG_MAX);
	COMPARE_PRINTF("|%llu|", ULLONG_MAX);
	COMPARE_PRINTF("|%llx|", ULLONG_MAX);
	// with # flag
	COMPARE_PRINTF("|%#o|", 99);
	COMPARE_PRINTF("|%#x|%#X|", 99, 99);
	//      with 0
	COMPARE_PRINTF("|%#o|", 0);
	COMPARE_PRINTF("|%#x|%#X|", 0, 0);
	//           with precision
	COMPARE_PRINTF("|%#.0o|%#.1o|%#.2o|", 0, 0, 0);
	COMPARE_PRINTF("|%#.0x|%#.1x|%#.2x|", 0, 0, 0);
	//           with field width
	COMPARE_PRINTF("|%#1o|%#2o|%#3o|", 0, 0, 0);
	COMPARE_PRINTF("|%#1x|%#2x|%#3x|", 0, 0, 0);
	//      with precision
	COMPARE_PRINTF("|%#.0o|%#.1o|%#.2o|", 9, 9, 9);
	COMPARE_PRINTF("|%#.0x|%#.1x|%#.2x|", 9, 9, 9);
	//      with field width
	COMPARE_PRINTF("|%#1o|%#2o|%#3o|", 9, 9, 9);
	COMPARE_PRINTF("|%#1x|%#2x|%#3x|", 9, 9, 9);
	// with 0 flag
	COMPARE_PRINTF("|%0d|%0d|%0d|", 9, 9, 9);
	COMPARE_PRINTF("|%0o|%0o|%0o|", 9, 9, 9);
	COMPARE_PRINTF("|%0u|%0u|%0u|", 9, 9, 9);
	COMPARE_PRINTF("|%0x|%0x|%0x|", 9, 9, 9);
	//      with field width
	COMPARE_PRINTF("|%01d|%02d|%03d|", 9, 9, 9);
	COMPARE_PRINTF("|%01o|%02o|%03o|", 9, 9, 9);
	COMPARE_PRINTF("|%01u|%02u|%03u|", 9, 9, 9);
	COMPARE_PRINTF("|%01x|%02x|%03x|", 9, 9, 9);
	//      with precision INVALID
	// with - flag
	COMPARE_PRINTF("|%-1d|%-1d|%-2d|%-2d|%-3d|%-3d|", -9, 9, -9, 9, -9, 9);
	COMPARE_PRINTF("|%-1o|%-2o|%-3o|", 9, 9, 9);
	COMPARE_PRINTF("|%-1u|%-2u|%-3u|", 9, 9, 9);
	COMPARE_PRINTF("|%-1x|%-2x|%-3x|", 9, 9, 9);
	// with ' ' flag
	COMPARE_PRINTF("|% d|% d|", -99, 99);
	// with + flag
	COMPARE_PRINTF("|%+d|%+d|", -99, 99);
	// with precision
	COMPARE_PRINTF("|%.1d|%.1d|%.2d|%.2d|%.3d|%.3d|", -9, 9, -9, 9, -9, 9);
	COMPARE_PRINTF("|%.1o|%.2o|%.3o|", 9, 9, 9);
	COMPARE_PRINTF("|%.1u|%.2u|%.3u|", 9, 9, 9);
	COMPARE_PRINTF("|%.1x|%.2x|%.3x|", 9, 9, 9);
	//      empty
	COMPARE_PRINTF("|%.d|%.d|", -99, 99);
	COMPARE_PRINTF("|%.o|", 99);
	COMPARE_PRINTF("|%.u|", 99);
	COMPARE_PRINTF("|%.x|", 99);
	//      negative
	/* COMPARE_PRINTF("|%.-1d|", 10); */
	// with field width
	COMPARE_PRINTF("|%1d|%1d|%2d|%2d|%3d|%3d|%4d|%4d|%5d|%5d|",
				   -99, 99, -99, 99, -99, 99, -99, 99, -99, 99);
	COMPARE_PRINTF("|%1o|%2o|%3o|%4o|", 99, 99, 99, 99);
	COMPARE_PRINTF("|%1u|%2u|%3u|%4u|", 99, 99, 99, 99);
	COMPARE_PRINTF("|%1x|%2x|%3x|%4x|", 99, 99, 99, 99);
	//      with 0 flag
	COMPARE_PRINTF("|%01d|%01d|%02d|%02d|%03d|%03d|%04d|%04d|%05d|%05d|",
				   -99, 99, -99, 99, -99, 99, -99, 99, -99, 99);
	COMPARE_PRINTF("|%01o|%02o|%03o|%04o|%05o|", 99, 99, 99, 99, 99);
	COMPARE_PRINTF("|%01u|%02u|%03u|%04u|%05u|", 99, 99, 99, 99, 99);
	COMPARE_PRINTF("|%01x|%02x|%03x|%04x|%05x|", 99, 99, 99, 99, 99);
	//      with - flag
	COMPARE_PRINTF("|%-1d|%-1d|%-2d|%-2d|%-3d|%-3d|%-4d|%-4d|%-5d|%-5d|",
				   -99, 99, -99, 99, -99, 99, -99, 99, -99, 99);
	COMPARE_PRINTF("|%-1o|%-2o|%-3o|%-4o|%-5o|", 99, 99, 99, 99, 99);
	COMPARE_PRINTF("|%-1u|%-2u|%-3u|%-4u|%-5u|", 99, 99, 99, 99, 99);
	COMPARE_PRINTF("|%-1x|%-2x|%-3x|%-4x|%-5x|", 99, 99, 99, 99, 99);
	//      with space flag
	COMPARE_PRINTF("|% 1d|% 1d|% 2d|% 2d|% 3d|% 3d|% 4d|% 4d|% 5d|% 5d|",
				   -99, 99, -99, 99, -99, 99, -99, 99, -99, 99);
	//      with plus flag
	COMPARE_PRINTF("|%+1d|%+1d|%+2d|%+2d|%+3d|%+3d|%+4d|%+4d|%+5d|%+5d|",
				   -99, 99, -99, 99, -99, 99, -99, 99, -99, 99);
	// with length modifier
	COMPARE_PRINTF("|%hhd|%hhd|%hhd|%hhd|", (char)CHAR_MIN, (char)-1, (char)0, (char)CHAR_MAX);
	COMPARE_PRINTF("|%hd|%hd|%hd|%hd|", (short)SHRT_MIN, (short)-1, (short)0, (short)SHRT_MAX);
	COMPARE_PRINTF("|%d|%d|%d|%d|", INT_MIN, -1, 0, INT_MAX);
	COMPARE_PRINTF("|%ld|%ld|%ld|%ld|", LONG_MIN, -1L, 0L, LONG_MAX);
	COMPARE_PRINTF("|%lld|%lld|%lld|%lld|", LLONG_MIN, -1LL, 0LL, LLONG_MAX);
	COMPARE_PRINTF("|%hho|%ho|%o|%lo|%llo|", (unsigned char)0, (unsigned short)0, 0, 0UL, 0ULL);
	COMPARE_PRINTF("|%hho|%ho|%o|%lo|%llo|", (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX);
	COMPARE_PRINTF("|%hhu|%hu|%u|%lu|%llu|", (unsigned char)0, (unsigned short)0, 0, 0UL, 0ULL);
	COMPARE_PRINTF("|%hhu|%hu|%u|%lu|%llu|", (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX);
	COMPARE_PRINTF("|%hhx|%hx|%x|%lx|%llx|", (unsigned char)0, (unsigned short)0, 0, 0UL, 0ULL);
	COMPARE_PRINTF("|%hhx|%hx|%x|%lx|%llx|", (unsigned char)UCHAR_MAX, (unsigned short)USHRT_MAX, UINT_MAX, ULONG_MAX, ULLONG_MAX);

	// f
	COMPARE_PRINTF("|%f|", 3.1415926535);
	COMPARE_PRINTF("|%f|", 3.0000000000);
	COMPARE_PRINTF("|%.30f|", 10000000000003.9875434567888888888888888888);
	// with negative number
	COMPARE_PRINTF("|%f|", -3.14);
	// with 0
	COMPARE_PRINTF("|%f|%f|%+f|% f|", -0.0, 0.0, 0.0, 0.0);
	// with infinity
	COMPARE_PRINTF("|%f|%f|%F|%F|", -INFINITY, INFINITY, -INFINITY, INFINITY);
	// with NaN
	COMPARE_PRINTF("|%f|%F|", NAN, NAN);
	#if ! __APPLE__
	// with -NaN
	COMPARE_PRINTF("|%f|%F|", -NAN, -NAN);
	//      with + flag
	COMPARE_PRINTF("|%+f|%+f|%+F|%+F|", -NAN, NAN, -NAN, NAN);
	//      with space flag
	COMPARE_PRINTF("|% f|% f|% F|% F|", -NAN, NAN, -NAN, NAN);
	#endif
	// with # flag
	COMPARE_PRINTF("|%#.0f|", 3.1);
	// with precision
	//      bigger than value
	COMPARE_PRINTF("|%.8f|", 3.1415);
	//      smaller than value
	COMPARE_PRINTF("|%.2f|", 3.1415);
	//      and empty precision
	COMPARE_PRINTF("|%.f|", 3.1415);
	//      and precision 0
	COMPARE_PRINTF("|%.0f|", 3.1415);
	//          rouding
	COMPARE_PRINTF("|%.0f|%.0f|%.0f|%.0f|%.0f|%.0f|", 1.4, 1.5, -1.6, 2.6, 2.5, -2.4);
	COMPARE_PRINTF("|%1.0f|", 9.5);
	//          rounding up
	COMPARE_PRINTF("|%.0f|%.0f|%.10f|%.10f|", -3.5, 3.5, -10.12345679995, 10.12345679995);
	COMPARE_PRINTF("|%.2f|%.2f|", -19.995, 19.995);
	//          rounding down
	COMPARE_PRINTF("|%.0f|%.0f|%.10f|%.10f|", -3.4, 3.4, -10.12345679994, 10.12345679994);
	//          with # flag
	COMPARE_PRINTF("|%#.0f|", 3.1415);
	// with length modifier
	COMPARE_PRINTF("|%.15Lf|", 3.14444444444L);

	// flags
	//     space before 0
	COMPARE_PRINTF("% 05d", 42);
	//     + before 0
	COMPARE_PRINTF("%+05d", 42);
	// multiple flags
	COMPARE_PRINTF("|%0 d|%0 d|", -99, 99);
	COMPARE_PRINTF("|% .4d|% .4d|", -99, 99);
	COMPARE_PRINTF("|%- d|%- d|", -99, 99);
	COMPARE_PRINTF("|%0+d|%0+d|", -99, 99);
	COMPARE_PRINTF("|%+.4d|%+.4d|", -99, 99);
	COMPARE_PRINTF("|%-+d|%-+d|", -99, 99);
	COMPARE_PRINTF("|%0 6d|%0 6d|", -99, 99);
	COMPARE_PRINTF("|% 6.4d|% 6.4d|", -99, 99);
	COMPARE_PRINTF("|%- 6d|%- 6d|", -99, 99);
	COMPARE_PRINTF("|%0+6d|%0+6d|", -99, 99);
	COMPARE_PRINTF("|%+6.4d|%+6.4d|", -99, 99);
	COMPARE_PRINTF("|%-+6d|%-+6d|", -99, 99);

	// different sizes chained
	COMPARE_PRINTF("%hhd %d %d %hhd", (char)42, INT_MIN, INT_MAX, (char)-42);

	// TODO Test return value of other functions?
}

int main()
{
	RUN_TEST(test_apppend_nchar);
	RUN_TEST(test_prepend_nchar);

	RUN_TEST(test_parse_conversion);

	/* RUN_TEST(test_printf_and_sprintf); */
	test_printf_and_sprintf();
}
