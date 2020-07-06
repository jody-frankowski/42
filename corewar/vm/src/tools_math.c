/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:10:42 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/26 22:41:53 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ft_absolute() - Return absolute value of @nb
*/

int		ft_absolute(int nb)
{
	if (nb < 0)
		nb = -nb;
	return (nb);
}
