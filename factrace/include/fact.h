/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fact.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/16 21:31:22 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/16 21:31:22 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef _FACT_H
# define _FACT_H

# include "gmp.h"

# define RHO_CONST 101359

int		prho(mpz_t n, unsigned long limit);
void	initialize_fact(void);
void	terminate_fact(void);

mpz_t n;
mpz_t x;
mpz_t y;
mpz_t d;

#endif
