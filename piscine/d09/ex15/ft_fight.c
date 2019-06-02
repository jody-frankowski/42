/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fight.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 15:14:46 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 15:14:47 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_fight.h"
#include "ft_perso.h"

#include <unistd.h>

void	ft_putstr(char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

void	ft_fight(t_perso *attacker, t_perso *attacked, t_attack attack)
{
	if (attacker->life <= 0 && attacked->life <= 0)
		return ;
	if (attacker->life <= 0)
		return ;
	ft_putstr(attacker->name);
	ft_putstr(" does a ");
	ft_putstr(attack.name);
	ft_putstr(" on ");
	ft_putstr(attacked->name);
	ft_putstr(".\n");
	if (attacked->life > 0)
	{
		attacked->life -= attack.points;
		if (attacked->life <= 0)
		{
			ft_putstr(attacked->name);
			ft_putstr(" is dead.\n");
		}
	}
}
