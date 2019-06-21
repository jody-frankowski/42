/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/15 18:48:30 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 18:48:30 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

void			*ft_bstrdup(void *src, size_t len);
int				ft_bstrtrunc(void **src, size_t start, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_lstfree(t_list **list, void *content);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstpush(t_list **lst, t_list *new);
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void			*ft_reallocf(void *ptr, size_t old_size, size_t new_size);
char			*ft_strndup(const char *s1, size_t n);

#endif
