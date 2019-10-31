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

# include <string.h>

# define TEST_TIMEOUT "Timeout"

# define RUN_TEST(func) run_test(func, #func, __FILE__, __LINE__)

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
