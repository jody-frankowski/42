/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_ins_arg_type.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include "libft.h"

static void	check_arg_integer_value(t_check_data *data, t_bstr str)
{
	if (str.len > DIRECT_VALUE_MAX_LEN)
		perr(data, P_ERR_MSG_INS_VALUE_LEN, str.str, str.len);
	bstr_skip_char(&str, '-');
	check_syntax_charset(data, str, DECIMAL_VALUE_CHARSET);
}

static void	check_arg_type_register(t_check_data *data, t_bstr str)
{
	if (str.len == 0)
		perr(data, P_ERR_MSG_INS_MISS_REGISTER_NUMBER, str.str - 1, 1);
	check_arg_integer_value(data, str);
}

static void	check_arg_type_direct(t_check_data *data, t_bstr str)
{
	if (str.len == 0)
		perr(data, P_ERR_MSG_INS_MISS_DIRECT_VALUE, str.str - 1, 1);
	if (bstr_skip_char(&str, LABEL_CHAR[0]))
	{
		if (str.len == 0)
			perr(data, P_ERR_MSG_INS_MISS_LABEL_REF, str.str - 1, 1);
		check_syntax_charset(data, str, LABEL_CHARSET);
	}
	else
		check_arg_integer_value(data, str);
}

static void	check_arg_type_indirect(t_check_data *data, t_bstr str)
{
	if (bstr_skip_char(&str, LABEL_CHAR[0]))
	{
		if (str.len == 0)
			perr(data, P_ERR_MSG_INS_MISS_LABEL_REF, str.str - 1, 1);
		check_syntax_charset(data, str, LABEL_CHARSET);
	}
	else
		check_arg_integer_value(data, str);
}

void		check_syntax_ins_arg_type(t_check_data *data, t_bstr str)
{
	if (bstr_skip_char(&str, REGISTER_CHAR[0]))
		check_arg_type_register(data, str);
	else if (bstr_skip_char(&str, DIRECT_VALUE_CHAR[0]))
		check_arg_type_direct(data, str);
	else
		check_arg_type_indirect(data, str);
}
