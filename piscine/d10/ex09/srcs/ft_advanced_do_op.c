/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_advanced_do_op.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 18:27:55 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 18:27:58 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "do_op.h"
#include "ft_opp.h"
#include "libft.h"

int		ft_usage(int a, int b)
{
	t_opp	*opps;

	(void)a;
	(void)b;
	opps = g_opptab;
	ft_putstr("error : only [ ");
	while (*((*opps).operator))
	{
		ft_putstr((*opps).operator);
		ft_putstr(" ");
		opps++;
	}
	ft_putstr("] are accepted.\n");
	return (0);
}

int		is_valid(char **av)
{
	char *op1;
	char *op2;
	char *op;

	op1 = av[0];
	op = av[1];
	op2 = av[2];
	if (ft_strcmp(op2, "0") == 0)
	{
		if (ft_strcmp(op, "/") == 0)
		{
			ft_putstr("Stop : division by zero\n");
			return (0);
		}
		if (ft_strcmp(op, "%") == 0)
		{
			ft_putstr("Stop : modulo by zero\n");
			return (0);
		}
	}
	return (1);
}

void	calc(char **av)
{
	unsigned long	i;
	char			*op1;
	char			*op2;
	char			*op;

	op1 = av[0];
	op = av[1];
	op2 = av[2];
	if (!is_valid(av))
		return ;
	i = 0;
	while (i < sizeof(g_opptab) / sizeof(g_opptab[0]))
	{
		if (ft_strcmp(op, g_opptab[i].operator) == 0)
		{
			ft_putnbr(g_opptab[i].f(ft_atoi(op1), ft_atoi(op2)));
			ft_putstr("\n");
			return ;
		}
		i++;
	}
	g_opptab[sizeof(g_opptab) / sizeof(g_opptab[0]) - 1].f(0, 0);
}

int		main(int ac, char **av)
{
	ac--;
	av++;
	if (ac != 3)
		return (-1);
	calc(av);
}
