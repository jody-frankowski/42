/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libunit.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/11 18:17:16 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/11 18:17:16 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBUNIT_H
# define LIBUNIT_H

# include <stdio.h>
# include <string.h>

# define RUN_TEST(func) run_test(func, #func, __FILE__, __LINE__)

/*
** ASSERT - Assert something and print an error if false
** @left:  The first operand
** @op:    A C operator
** @right: The second operand
*/
# define ASSERT(left, op, right) do { \
	typeof(left) _left = (left); \
	typeof(right) _right = (right); \
	if (!(_left op _right)) \
	{ \
		dprintf( \
			2, \
			"%s@(%s:%d): %s !%s %s (%#llx !%s %#llx)\n", \
			__func__, __FILE__, __LINE__, #left, #op, #right, \
			(unsigned long long)_left, #op, (unsigned long long)_right); \
	} \
} while (0)

/*
** ASSERT_OBJ - Assert something about two objects and print them if error
** @cmp:   A function that compares @left and @right, called like so:
**         cmp(fd, typeof(left|right))
** @left:  The first operand.
** @right: The second operand
** @op:    A C expression that will make "cmp(left, right) op" evaluate properly
** @print: A function that can print @left and @right and takes a file
**         descriptor as a first argument, called like so:
**         print(fd, typeof(left|right), @len)
*/

# define ASSERT_OBJ(cmp, left, right, op, print) do { \
	typeof(left) _left = (left); \
	typeof(right) _right = (right); \
	if (!(cmp(_left, _right)) op) \
	{ \
		dprintf( \
			2, \
			"%s@(%s:%d): %s(%s, %s) !%s:\n", \
			__func__, __FILE__, __LINE__, #cmp, #left, #right, #op); \
		print(2, _left); \
		dprintf(2, "\n"); \
		print(2, _right); \
		dprintf(2, "\n"); \
	} \
} while (0)

/*
** ASSERT_NOBJ - Assert something about two objects and print them if error
** @cmp:   A function that compares @left and @right, called like so:
**         cmp(fd, typeof(left|right), @len)
** @left:  The first operand.
** @right: The second operand
** @len:   A length to limit the @cmp and @print functions
** @op:    A C expression that will make "cmp(left, right) op" evaluate properly
** @print: A function that can print @left and @right and takes a file
**         descriptor as a first argument, called like so:
**         print(fd, typeof(left|right), @len)
*/

# define ASSERT_NOBJ(cmp, left, right, len, op, print) do { \
	typeof(left) _left = (left); \
	typeof(right) _right = (right); \
	if (!(cmp(_left, _right, len)) op) \
	{ \
		dprintf( \
			2, \
			"%s@(%s:%d): %s(%s, %s) !%s:\n", \
			__func__, __FILE__, __LINE__, #cmp, #left, #right, #op); \
		print(2, _left, len); \
		dprintf(2, "\n"); \
		print(2, _right, len); \
		dprintf(2, "\n"); \
	} \
} while (0)

# define ASSERT_MEM_EQ(a, b, len) \
	assert_mem_eq(#a, #b, __FILE__, __func__, __LINE__, a, b, len)

# define ASSERT_PTR_EQ(a, b) \
	assert_ptr_eq(#a, #b, __func__, __FILE__, __LINE__, a, b)

# define ASSERT_STR_EQ(a, b) \
	assert_str_eq(#a, #b, __func__, __FILE__, __LINE__, a, b)

// TODO Decide if start/stop fd captures need a macro wrapper

int assert_mem_eq(
					 const char *a_tok,
					 const char *b_tok,
					 const char *func,
					 const char *file,
					 size_t line,
					 const void *a,
					 const void *b,
					 size_t len
				  );
int assert_ptr_eq(
					 const char *a_tok,
					 const char *b_tok,
					 const char *func,
					 const char *file,
					 size_t line,
					 const void *a,
					 const void *b
					 );
int assert_str_eq(
					 const char *a_tok,
					 const char *b_tok,
					 const char *func,
					 const char *file,
					 size_t line,
					 const char *a,
					 const char *b
					 );
int start_fd_capture(int fd);
int stop_fd_capture(int fd, char **output);
void	run_test(void (*func)(void), const char *name, const char *file, size_t line);

#endif
