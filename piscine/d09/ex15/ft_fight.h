/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fight.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 15:11:23 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 15:11:24 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_FIGHT_H
# define FT_FIGHT_H

typedef struct	s_attack
{
	char	*name;
	int		points;
}				t_attack;

# define KICK (t_attack){"judo kick", 15}
# define PUNCH (t_attack){"judo punch", 5}
# define HEADBUTT (t_attack){"judo headbutt", 20}

#endif
