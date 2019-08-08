#ifndef LIBTEST_H
# define LIBTEST_H

# include <string.h>

#define ASSERT_EQUAL_BOOL(a, b) \
	assert_equal_bool(#a, #b, __FILE__, __func__, __LINE__, a, b)

#define ASSERT_EQUAL_INT(a, b) \
	assert_equal_int(#a, #b, __FILE__, __func__, __LINE__, a, b)

#define ASSERT_EQUAL_MEM(a, b, n) \
	assert_equal_mem(#a, #b, __FILE__, __LINE__, a, b, n)

#define ASSERT_EQUAL_PTR(a, b) \
	assert_equal_ptr(#a, #b, __FILE__, __func__, __LINE__, a, b)

#define ASSERT_EQUAL_STR(a, b) \
	assert_equal_str(#a, #b, __FILE__, __func__, __LINE__, a, b)

#define ASSERT_NOT_EQUAL_INT(a, b)										\
	assert_not_equal_int(#a, #b, __FILE__, __func__, __LINE__, a, b)

#define ASSERT_NOT_EQUAL_MEM(a, b, n)							\
	assert_not_equal_mem(#a, #b, __FILE__, __LINE__, a, b, n)

#define ASSERT_NOT_EQUAL_PTR(a, b)										\
	assert_not_equal_ptr(#a, #b, __FILE__, __func__, __LINE__, a, b)

#define ASSERT_NOT_EQUAL_STR(a, b)										\
	assert_not_equal_str(#a, #b, __FILE__, __func__, __LINE__, a, b)

#define ASSERT_FALSE(a) \
	assert_false(#a, __FILE__, __func__, __LINE__, a)

#define ASSERT_TRUE(a) \
	assert_true(#a, __FILE__, __func__, __LINE__, a)

int assert_false(const char *a_tok, const char *file, const char *func, size_t line, int a);
int assert_true(const char *a_tok, const char *file, const char *func, size_t line, int a);
int assert_equal_bool(const char *a_tok, const char *b_tok, const char *file, \
					 const char *func, size_t line, int a, int b);
int assert_equal_int(const char *a_tok, const char *b_tok, const char *file, \
					 const char *func, size_t line, int a, int b);
int assert_equal_mem(const char *a_tok, const char *b_tok, const char *file, \
					 size_t line, const void *a, const void *b, size_t n);
int assert_equal_ptr(const char *a_tok, const char *b_tok, const char *file, \
					 const char *func, size_t line, const void *a, const void *b);
int assert_equal_str(const char *a_tok, const char *b_tok, const char *file, \
					 const char *func, size_t line, const char *a, const char *b);
int assert_not_equal_int(const char *a_tok, const char *b_tok, const char *file, \
					 const char *func, size_t line, int a, int b);
int assert_not_equal_mem(const char *a_tok, const char *b_tok, const char *file, \
					 size_t line, const void *a, const void *b, size_t n);
int assert_not_equal_ptr(const char *a_tok, const char *b_tok, const char *file, \
					 const char *func, size_t line, const void *a, const void *b);
int assert_not_equal_str(const char *a_tok, const char *b_tok, const char *file, \
					 const char *func, size_t line, const char *a, const char *b);

void	print_hex(const void *data, int n);

#endif
