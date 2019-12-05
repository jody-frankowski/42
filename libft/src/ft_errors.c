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
** @is_error: The value to check for
**
** ft_err_exit will output @error_message and exit when @is_error is true
*/

void	ft_err_exit(int is_error, const char *error_message)
{
	if (is_error)
	{
		ft_putstr_fd(2, error_message);
		exit(-1);
	}
}
