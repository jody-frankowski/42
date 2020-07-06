/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
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
