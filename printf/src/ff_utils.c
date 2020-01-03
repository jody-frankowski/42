/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ff_utils.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/22 17:43:30 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/22 17:43:30 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdint.h>
#include "libftprintf.h"

/*
** ft_signbit_ld() - Get the sign of a long double
** @num: The long double from which to get the sign
**
** BUG: We don't use an enum/struct combo.
**
** Return: 1 if the sign bit is set. 0 if not.
*/

int			ft_signbit_ld(long double num)
{
	return ((((uint64_t*)&num)[1] >> 15) & 1);
}

long double	get_num_ld(va_list args, t_conv conv)
{
	if (conv.length_modifier_flag)
	{
		if (conv.length_modifier == LF)
			return ((long double)va_arg(args, long double));
	}
	return ((double)va_arg(args, double));
}
