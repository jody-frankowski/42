/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ultimate_fight.h                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 16:47:17 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 16:47:20 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_ULTIMATE_FIGHT_H
# define FT_ULTIMATE_FIGHT_H

typedef struct	s_attack
{
	int		points;
	char	*name;
}				t_attack;

# define KICK (t_attack){15, "judo kick"}
# define KICK2(t_attack){3, "judo chop ni"}
# define KICK3(t_attack){18, "judo chop san"}
# define KICK4(t_attack){9, "judo chop shi"}
# define KICK5(t_attack){11, "judo chop go"}
# define KICK6(t_attack){13, "judo chop roku"}
# define KICK7(t_attack){8, "judo chop shichi"}
# define KICK8(t_attack){6, "judo chop hachi"}
# define KICK9(t_attack){11, "judo chop ku"}
# define KICK10(t_attack){9, "judo chop ju"}
# define KICK11(t_attack){18, "judo chop hyaku"}
# define KICK12(t_attack){10, "judo chop sen"}
# define PUNCH (t_attack){5, "judo punch"}
# define HEADBUTT (t_attack){20, "judo headbutt"}

#endif
