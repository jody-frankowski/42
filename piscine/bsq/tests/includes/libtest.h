/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libtest.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/23 15:04:16 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/23 15:04:17 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef _LIBTEST_H
# define _LIBTEST_H

# include <stdlib.h>

void	assert_equal_array(const void *s1, const void *s2, unsigned long n);
void	assert_equal_int(int a, int b);
void	assert_equal_str(char *s1, char *s2);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_putnbr_fd(int fd, int nbr);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *src);

#endif
