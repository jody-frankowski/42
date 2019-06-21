/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 18:19:58 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 18:19:58 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>

# define PRINT_BUF_SIZE 65536
# define TAB_LEN 32768

typedef struct	s_tab
{
	char			*key;
	char			*data;
	struct s_tab	*next;
}				t_tab;

char			*g_buf;
char			*g_buf_ptr;
size_t			g_buf_size;
char			g_print_buf[PRINT_BUF_SIZE];
size_t			g_print_buf_size;
t_tab			g_tab[TAB_LEN];

void			*ft_memcpy(
						void *dst,
						const void *src,
						size_t n); __attribute__((always_inline))
int				keycmp(
					const char *key1,
					const char *key2,
					uint8_t key1_len); __attribute__((always_inline))
void			free_tab(); __attribute__((always_inline))

void			print(char *str, size_t n); __attribute__((always_inline))
void			print_flush(); __attribute__((always_inline))
void			print_data(
						char *data,
						uint8_t length); __attribute__((always_inline))
void			ft_read_all(int fd); __attribute__((always_inline))
int				treat_dict();
int				cheat();

#endif
