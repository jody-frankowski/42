/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bigint.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/06 00:43:56 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/06 00:43:56 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BIGINT_H
# define BIGINT_H

# define BIGINT_NEG 1
# define BIGINT_POS 0

# define BIGINT_MAX ULONG_MAX
# define BIGINT_MIN ULONG_MAX

typedef unsigned long	t_bigint_val;

typedef struct	s_bigint {
	unsigned int	sign:1;
	unsigned int	size;
	t_bigint_val	*val;
}				t_bigint[1];

void			bigint_free(t_bigint num);
int				bigint_init(t_bigint num);

int				bigint_set(t_bigint res, t_bigint num);
void			bigint_set_si(t_bigint res, signed long si);
void			bigint_set_ui(t_bigint res, unsigned long ui);

#endif
