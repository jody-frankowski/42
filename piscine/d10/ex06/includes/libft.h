/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 00:35:38 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 00:35:40 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

int		ft_atoi(char *str);
void	ft_putchar(char c);
void	ft_putnbr(int nbr);
void	ft_putstr(char *str);
int		ft_strcmp(char *s1, char *s2);

int		ft_add(int a, int b);
int		ft_div(int a, int b);
int		ft_mod(int a, int b);
int		ft_mul(int a, int b);
int		ft_sub(int a, int b);

#endif
