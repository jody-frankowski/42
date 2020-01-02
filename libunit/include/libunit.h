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
** @left:      The first operand
** @condition: A C operator
** @right:     The second operand
**
** Like kunit we compare @left and @right with their proper types, but cast them
** to unsigned long long when printing in order not to have to bother with more
** types.
*/
# define ASSERT(left, condition, right) do { \
	typeof(left) _left = (left); \
	typeof(right) _right = (right); \
	if (!(_left condition _right)) \
	{ \
		dprintf( \
			2, \
			"%s@(%s:%d): %s !%s %s (%#llx !%s %#llx)\n", \
			__func__, __FILE__, __LINE__, #left, #condition, #right, \
			(unsigned long long)_left, #condition, (unsigned long long)_right); \
	} \
} while (0)

/*
** ASSERT_OBJ - Assert something about two objects and print them if error
** @cmp:       A function that compares @left and @right, called like so:
**             cmp(fd, @left|right)
** @left:      The first operand.
** @right:     The second operand
** @condition: A C expression that will make "cmp(@left, @right) @condition"
**             evaluate properly
** @print:     A function that can print @left and @right and takes a file
**             descriptor as a first argument, called like so:
**             print(fd, @left|@right, @len)
*/

# define ASSERT_OBJ(cmp, left, right, condition, print) do { \
	typeof(left) _left = (left); \
	typeof(right) _right = (right); \
	if (!((cmp(_left, _right)) condition)) \
	{ \
		dprintf( \
			2, \
			"%s@(%s:%d): %s(%s, %s) !%s:\n", \
			__func__, __FILE__, __LINE__, #cmp, #left, #right, #condition); \
		print(2, _left); \
		dprintf(2, "\n"); \
		print(2, _right); \
		dprintf(2, "\n"); \
	} \
} while (0)

/*
** ASSERT_NOBJ - Assert something about two objects and print them if error
** @cmp:       A function that compares @left and @right, called like so:
**             cmp(fd, @left|@right, @len)
** @left:      The first operand.
** @right:     The second operand
** @len:       A length to limit the @cmp and @print functions
** @condition: A C expression that will make "cmp(@left, @right) @condition"
**             evaluate properly
** @print:     A function that can print @left and @right and takes a file
**             descriptor as a first argument, called like so:
**             print(fd, @left|@right, @len)
*/

# define ASSERT_NOBJ(cmp, left, right, len, condition, print) do { \
	typeof(left) _left = (left); \
	typeof(right) _right = (right); \
	if (!((cmp(_left, _right, len)) condition)) \
	{ \
		dprintf( \
			2, \
			"%s@(%s:%d): %s(%s, %s) !%s:\n", \
			__func__, __FILE__, __LINE__, #cmp, #left, #right, #condition); \
		print(2, _left, len); \
		dprintf(2, "\n"); \
		print(2, _right, len); \
		dprintf(2, "\n"); \
	} \
} while (0)

int	start_fd_capture(int fd);
int	stop_fd_capture(int fd, char **output);
void	run_test(void (*func)(void),
				const char *name,
				const char *file,
				size_t line);

#endif
