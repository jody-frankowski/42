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

static	mpz_t n;
static	mpz_t x;
static	mpz_t y;
static	mpz_t d;

#endif
