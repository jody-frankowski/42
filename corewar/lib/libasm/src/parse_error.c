/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

static void	push_parse_error(t_check_data *check_data,
									t_parse_error *parse_error)
{
	parse_error->line = check_data->line;
	parse_error->line_num = check_data->line_num;
	if (!ft_array_push(check_data->parsing_errors, parse_error))
	{
		if (check_data->parsing_errors)
		{
			ft_array_free(check_data->parsing_errors);
			check_data->parsing_errors = NULL;
		}
	}
}

/*
** perr() - Add a parsing error
** @data  : The check data to add the error to
** @msg:    The message of the error
** @column: The column where the error starts
** @len:    The length of th error
*/

void		perr(t_check_data *data,
					t_parse_error_msg msg,
					char *column,
					size_t len)
{
	t_parse_error	parse_error;

	parse_error = (t_parse_error){
									.type = P_ERR_TYPE_ERROR,
									.msg = msg,
									.column = column,
									.len = len,
								};
	push_parse_error(data, &parse_error);
}

/*
** pwarn() - Add a parsing warning
** @data  : The check data to add the warning to
** @msg:    The message of the error
** @column: The column where the error starts
** @len:    The length of th error
*/

void		pwarn(t_check_data *data,
					t_parse_error_msg msg,
					char *column,
					size_t len)
{
	t_parse_error	parse_error;

	parse_error = (t_parse_error){
									.type = P_ERR_TYPE_WARNING,
									.msg = msg,
									.column = column,
									.len = len,
								};
	push_parse_error(data, &parse_error);
}
