/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   do_op.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 18:48:41 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 18:48:42 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "do_op.h"
#include "libft.h"

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
	ft_putnbr(0);
	ft_putstr("\n");
}

int		main(int ac, char **av)
{
	ac--;
	av++;
	if (ac != 3)
		return (-1);
	calc(av);
}
