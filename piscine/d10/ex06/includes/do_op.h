/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   do-op.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 19:01:09 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 19:01:13 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DO_OP_H
# define DO_OP_H

# include "libft.h"
# include <stdlib.h>

typedef struct	s_opp
{
	char	*operator;
	int		(*f)(int, int);
}				t_opp;

t_opp g_opptab[] =
{
	{"-", &ft_sub},
	{"+", &ft_add},
	{"*", &ft_mul},
	{"/", &ft_div},
	{"%", &ft_mod},
};

#endif
