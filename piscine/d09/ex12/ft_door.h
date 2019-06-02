/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_door.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/13 16:28:09 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/13 16:28:10 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_DOOR_H
# define FT_DOOR_H

typedef int	t_ft_bool;

typedef struct	s_door
{
	t_ft_bool state;
}				t_door;

# define OPEN 1
# define CLOSE 0

#endif
