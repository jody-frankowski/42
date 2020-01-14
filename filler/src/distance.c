/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   distance.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/06 00:43:56 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/06 00:43:56 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"

static int		ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

static int		ft_square(int nb)
{
	return (nb * nb);
}

static float	ft_fsqrt(const float x)
{
	union u_float	u;
	float			xhalf;

	xhalf = 0.5f * x;
	u.x = x;
	u.i = 0x5f3759df - (u.i >> 1);
	return (x * u.x * (1.5f - xhalf * u.x * u.x));
}

float			distance(t_coord a, t_coord b)
{
	return (ft_fsqrt(ft_square(ft_abs(a.x - b.x)) +
					ft_square(ft_abs(a.y - b.y))));
}
