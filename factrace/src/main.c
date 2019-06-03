/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_parsing.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: epoggio <epoggio@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/15 18:50:49 by epoggio      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/15 23:05:04 by epoggio     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include "fact.h"
#include "line.h"

void		algo(int i, t_lines lines, mpz_t timeout)
{
	int last_to_overflow;
	unsigned long ctr_limit;
	mpz_t ctr_limit_mpz;

	initialize_fact();
	mpz_init(ctr_limit_mpz);
	mpz_mul_ui(timeout, timeout, 1000);
	if (lines.max > 30)
	{
		mpz_fdiv_q_ui(ctr_limit_mpz, timeout, 100);
		ctr_limit = mpz_get_ui(ctr_limit_mpz);
	}
	else
	{
		mpz_fdiv_q_ui(ctr_limit_mpz, timeout, 30);
		ctr_limit = mpz_get_ui(ctr_limit_mpz);
	}

	i = 1;
	while (i < lines.max)
	{
		if (lines.ll[i].len >= lines.ll[i - 1].len + 3)
			last_to_overflow = i;
		i++;
	}
	mpz_set_str(n, lines.ll[last_to_overflow].str, 10);
	prho(n, 50000);

	i = lines.max - 1;
	while (i >= 0)
	{
		mpz_set_str(n, lines.ll[i].str, 10);
		if (prho(n, ctr_limit))
			break ;
		i--;
	}
	terminate_fact();
	mpz_clear(timeout);
}

int			main(int ac, char **av)
{
	char	buff[BUFFER + 1];
	int		i;
	int		ret;
	t_lines	lines;
	mpz_t	timeout;

	if (ac == 2)
		mpz_init_set_str(timeout, av[1], 10);
	lines = (t_lines){{{{0}, 0, 0}}, 0};
	i = 0;
	if ((ret = read(0, buff, BUFFER)) > 0)
	{
		buff[ret] = 0;
		while (lines.max < MAX_LINE && i < ret)
		{
			if (i >= BUFFER)
			{
				lines.max--;
				break ;
			}
			if (buff[i] == '\n')
				lines.ll[lines.max++].num = lines.max + 1;
			else
				lines.ll[lines.max].str[lines.ll[lines.max].len++] = buff[i];
			i++;
		}
	}
	algo(i, lines, timeout);
	return (0);
}
