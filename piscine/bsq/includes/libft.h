/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 11:52:24 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/25 19:36:59 by tiperoul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef _LIBFT_H
# define _LIBFT_H
# define BUF_SIZE 4194304
# include <stdint.h>
# include <stdlib.h>

typedef struct	s_spec
{
	uint32_t	c;
	uint32_t	l;
	char		empty;
	char		obstacle;
	char		full;
}				t_spec;

typedef struct	s_point
{
	uint32_t	l;
	uint32_t	c;
	int			max;
}				t_point;

int				ft_atoi(char *str);
void			*ft_memcpy(void *restrict dst, void *restrict src);
int				ft_min(int a, int b, int c);
void			ft_putchar(char c);
void			ft_putchar_fd(int fd, char c);
void			ft_putnbr(int nbr, uint32_t padding);
void			ft_putstr(char *str);
void			ft_putstr_fd(int fd, char *str);
void			*ft_realloc(void *ptr, size_t size);
char			*ft_strcat(char *dest, char *src);
int				ft_strlen(char *str);
char			*ft_strndup(char *src, size_t n);

int				treat(char *input);
int				treat2(char *input, t_spec *spec);
int				treat3(int **grid, char *input, char *save, t_spec *spec);

int				neighbors(int **grid, char *input, t_spec *spec, t_point *p);
int				calc_coord(t_point *p, t_spec *spec);

int				**alloc_grid(t_spec *spec);
int				free_grid(int **grid, uint32_t l);
void			print_grid(char *input, t_spec *spec);

int				spec_valid(char *line);
t_spec			*get_spec(char *line);
int				in_spec(char c, t_spec *spec);

t_point			g_max;

#endif
