/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_errors.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/08 15:58:24 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/08 15:58:24 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_err_exit(int statement_value, const char *error_message)
{
	if (statement_value)
	{
		ft_putstr_fd(error_message, 2);
		exit(-1);
	}
}
