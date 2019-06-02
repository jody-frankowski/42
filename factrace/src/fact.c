/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fact.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/17 10:40:18 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/17 10:40:18 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fact.h"

void				initialize_fact(void)
{
	mpz_init(n);
	mpz_init(x);
	mpz_init(y);
	mpz_init(d);
}

void				terminate_fact(void)
{
	mpz_clear(n);
	mpz_clear(x);
	mpz_clear(y);
	mpz_clear(d);
}

/*
** f(x) = (x^2 + c) mod n, c != 0,-2
*/

void				f(mpz_t x, mpz_t n)
{
	mpz_pow_ui(x, x, 2);
	mpz_add_ui(x, x, RHO_CONST);
	mpz_mod(x, x, n);
}

/*
** rho de Pollard :
**
** Inputs: n, the integer to be factored; and f(x)
**         a, pseudo-random function modulo n
**
** Output: a non-trivial factor of n, or failure.
**
** 1. x ← 2, y ← 2; d ← 1
** 2. While d = 1:
** 1.   x ← f(x)
** 2.   y ← f(f(y))
** 3.   d ← GCD(|x − y|, n)
** 3. If d = n, return failure.
** 4. Else, return d.
*/

int					prho(mpz_t n, unsigned long limit)
{
	unsigned long	ctr;

	ctr = 0;
	mpz_set_ui(x, 2);
	mpz_set_ui(y, 2);
	mpz_set_ui(d, 1);
	while (mpz_cmp_ui(d, 1) == 0 && ctr < limit)
	{
		f(x, n);
		f(y, n);
		f(y, n);
		mpz_sub(d, x, y);
		mpz_abs(d, d);
		mpz_gcd(d, d, n);
		ctr++;
	}
	if (mpz_cmp_ui(d, 1) != 0)
	{
		gmp_printf("%Zd=", n);
		gmp_printf("%Zd", d);
		mpz_tdiv_q(n, n, d);
		gmp_printf("*%Zd\n", n);
		return (1);
	}
	return (0);
}
