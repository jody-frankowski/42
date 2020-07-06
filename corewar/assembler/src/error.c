/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "assembler.h"

size_t	parse_errors_count_type_error(t_array *errors)
{
	size_t			i;
	size_t			count;
	t_parse_error	*error;

	count = 0;
	i = 0;
	while (i < errors->len)
	{
		error = ft_array_get(errors, i);
		if (error->type == P_ERR_TYPE_ERROR)
			count++;
		i++;
	}
	return (count);
}

void	err_exit(t_parse_data *parse_data)
{
	free_parse_data(parse_data);
	exit(1);
}
