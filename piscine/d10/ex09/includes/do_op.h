/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   do_op.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 18:49:17 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 18:49:18 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DO_OP_H
# define DO_OP_H

# include <stdlib.h>

typedef struct	s_opp
{
	char	*operator;
	int		(*f)(int, int);
}				t_opp;

#endif
