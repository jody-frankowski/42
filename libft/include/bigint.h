/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_H
# define BIGINT_H

# include <limits.h>
# include <stddef.h>

# define BIGINT_NEG 1
# define BIGINT_POS 0

# define BIGINT_MAX ULONG_MAX
# define BIGINT_MIN ULONG_MAX

/*
** # define BIGINT_VAL_NBIT (sizeof(t_bigint_val) * CHAR_BIT)
*/

# define BIGINT_VAL_NBIT 64

typedef unsigned long	t_bigint_val;

typedef struct	s_bigint {
	unsigned int	sign:1;
	unsigned int	size;
	t_bigint_val	*val;
}				t_bigint[1];

int				bigint_free(t_bigint num);
int				bigint_init(t_bigint num);
void			bigint_fix_size(t_bigint num);
int				bigint_alloc_one_more(t_bigint num);
int				bigint_realloc(t_bigint num, size_t new_size);

int				bigint_set(t_bigint res, t_bigint num);
void			bigint_set_si(t_bigint res, signed long si);
void			bigint_set_ui(t_bigint res, unsigned long ui);
int				bigint_abs(t_bigint rop, t_bigint op);

int				bigint_cmp(t_bigint op1, t_bigint op2);
int				bigint_cmpabs(t_bigint op1, t_bigint op2);
int				bigint_cmp_si(t_bigint op1, signed long op2);

int				bigint_add_abs(t_bigint res, t_bigint op1, t_bigint op2);
int				bigint_sub_abs(t_bigint res, t_bigint op1, t_bigint op2);
int				bigint_add(t_bigint res, t_bigint op1, t_bigint op2);
int				bigint_sub(t_bigint res, t_bigint op1, t_bigint op2);
int				bigint_sub_pos_neg(t_bigint res, t_bigint op1, t_bigint op2);
int				bigint_sub_neg_pos(t_bigint res, t_bigint op1, t_bigint op2);

int				bigint_add_ui(t_bigint res,
								t_bigint op1,
								unsigned long op2_bigint_ui);
int				bigint_sub_ui(t_bigint res,
								t_bigint op1,
								unsigned long op2_bigint_ui);

int				bigint_mul(t_bigint res, t_bigint op1, t_bigint op2);
int				bigint_mul_si(t_bigint res, t_bigint op1, signed long op2);

int				bigint_div(t_bigint q, t_bigint r, t_bigint op1, t_bigint op2);

int				bigint_get_bit(t_bigint num, size_t n);
void			bigint_set_bit(t_bigint num, size_t n, unsigned char val);
int				bigint_shift_left(t_bigint res, t_bigint op1);
size_t			bigint_num_bits(t_bigint num);

#endif
