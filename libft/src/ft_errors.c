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

/*
** ft_err_exit - Output an error message and exit depending on a value
** @statement_value: The value to check for
**
** ft_err_exit will output @error_message and exit when @statement_value is true
*/

void	ft_err_exit(int statement_value, const char *error_message)
{
	if (statement_value)
	{
		ft_putstr_fd(error_message, 2);
		exit(-1);
	}
}
