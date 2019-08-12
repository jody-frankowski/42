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

/*
** We suppose we are on a 64 bit machine with `long` being 64 bits.
** This should be the case for x86-64 machines with Linux, BSD and MacOs.
** Finding the word size of a machine seems to be hard at best,
** impossible at worst.
*/

# define WORDSIZE sizeof(unsigned long)

# define HEXDUMP_WIDTH 16

typedef unsigned char	t_byte;
typedef unsigned long	t_word;

typedef struct	s_array
{
	t_byte	*bytes;
	size_t	len;
	size_t	width;
	void	(*free)(void *);
}				t_array;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

int				ft_atoi(const char *str);
void			*ft_array_free(t_array *array);
void			*ft_array_get(t_array *array, size_t index);
void			*ft_array_get_ptr(t_array *array, size_t index);
t_array			*ft_array_new(size_t width, void (*free)(void *));
int				ft_array_push(t_array *array, void *data);
int				ft_array_push_ptr(t_array *array, void *ptr);
void			*ft_array_to_null_terminated(t_array *array);
void			*ft_bstrdup(void *src, size_t len);
int				ft_bstrtrunc(void **src, size_t start, size_t len);
void			ft_bzero(void *s, size_t n);
int				ft_charcasecmp(char c1, char c2);
size_t			ft_count_words(char const *s, char const *charset);
size_t			ft_count_words_c(char const *s, char c);
void			ft_err_exit(int statement_value, const char *error_message);
void			ft_hexdump(const void *ptr, size_t len);
int				ft_incharset(int c, const char *charset);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_islower(int c);
int				ft_isprint(int c);
int				ft_issorted(void *base, size_t nel, size_t width,
								int (*compar)(const void *, const void *));
int				ft_isspace(int c);
int				ft_isupper(int c);
char			*ft_itoa(int n);
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstfree(t_list **list, void *content);
int				ft_lstissorted(t_list *lst, int (*cmp)(t_list *, t_list *));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstmergesort(t_list **lst, int (*cmp)(t_list *, t_list *));
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstpush(t_list **lst, t_list *new);
void			*ft_memalloc(size_t size);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_memdel(void **ap);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
size_t			ft_num_digits(int n);
int				ft_pow(int base, int exponent);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putwchar(int c);
void			ft_putwchar_fd(int c, int fd);
void			ft_qsort(void *base, size_t nel, size_t width,
						int (*compar)(const void *, const void *));
int				ft_read_all(int fd, char **buf);
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void			*ft_reallocf(void *ptr, size_t size, size_t new_size);
char			*ft_stpcpy(char *dst, const char *src);
char			*ft_stpncpy(char *dst, const char *src, size_t len);
int				ft_strcasecmp(const char *s1, const char *s2);
char			*ft_strcasestr(const char *haystack, const char *needle);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strchr(const char *s, int c);
void			ft_strclr(char *s);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
size_t			ft_strcspn(const char *s, const char *charset);
void			ft_strdel(char **as);
char			*ft_strdup(const char *s1);
int				ft_strequ(char const *s1, char const *s2);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncasecmp(const char *s1, const char *s2, size_t n);
char			*ft_strncat(char *s1, const char *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strndup(const char *s1, size_t n);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strnew(size_t size);
size_t			ft_strnlen(const char *s, size_t maxlen);
char			*ft_strnstr(const char *haystack, const char *needle,
							size_t len);
char			*ft_strpbrk(const char *s, const char *charset);
char			*ft_strrchr(const char *s, int c);
char			*ft_strrev(char const *s);
char			**ft_strsplit(char const *s, char c);
size_t			ft_strspn(const char *s, const char *charset);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
long			ft_strtol(const char *restrict str,
						char **restrict endptr, int base);
char			*ft_strtrim(char const *s);
void			ft_swap(void *a, void *b, size_t len);
void			*ft_tab_free(void *tab,
							void (*free)(void *),
							size_t width,
							size_t len);
int				ft_tab_push(void **tab, void *data, size_t width, size_t len);
int				ft_tab_push_ptr(void **tab,
									void *ptr,
									size_t width,
									size_t len);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_read_up_to(int fd, char *buff, int to_read, int *total);

#endif
