/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_ins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include "libft.h"

static void	check_label_and_name(t_check_data *data, t_bstr *str)
{
	t_bstr	sub_str;
	size_t	count;

	sub_str = bstr_read_until(str, WSP""LABEL_CHAR""OPERANDS_SEPARATOR_CHAR);
	if (bstr_skip_char(str, LABEL_CHAR[0]))
	{
		check_syntax_charset(data, sub_str, LABEL_CHARSET);
		if (sub_str.len == 0)
			perr(data, P_ERR_MSG_INS_MISS_LABEL_NAME, str->str - 1, 1);
		count = bstr_skip_chars(str, WSP);
		if (str->len > 0 && count == 0)
			pwarn(data, P_ERR_MSG_INS_MISS_WSP_BETWEEN_LABEL_AND_INSTRUCTION,
					str->str, 0);
		sub_str = bstr_read_until(str, WSP""OPERANDS_SEPARATOR_CHAR);
	}
	if (str->len > 0 && sub_str.len == 0)
		perr(data, P_ERR_MSG_INS_MISS_NAME, sub_str.str, 0);
}

void		check_syntax_ins_arg(t_check_data *data, t_bstr *str)
{
	size_t	count;
	t_bstr	arg;

	bstr_skip_chars(str, WSP);
	count = bstr_skip_char(str, OPERANDS_SEPARATOR_CHAR[0]);
	if (str->len > 0 && count == 0)
		perr(data, P_ERR_MSG_INS_MISS_COMMA, str->str - 1, 0);
	bstr_skip_chars(str, WSP);
	arg = bstr_read_until(str, WSP""OPERANDS_SEPARATOR_CHAR);
	if (arg.len == 0)
		perr(data, P_ERR_MSG_INS_EMPTY_OPERAND, arg.str, 0);
	else
		check_syntax_ins_arg_type(data, arg);
}

void		check_syntax_ins(t_check_data *data, t_bstr str)
{
	t_bstr	arg;

	check_label_and_name(data, &str);
	bstr_skip_chars(&str, WSP);
	if (str.len > 0)
	{
		arg = bstr_read_until(&str, WSP""OPERANDS_SEPARATOR_CHAR);
		if (arg.len == 0)
			perr(data, P_ERR_MSG_INS_EMPTY_OPERAND, arg.str, 0);
		else
			check_syntax_ins_arg_type(data, arg);
	}
	if (str.len > 0)
		check_syntax_ins_arg(data, &str);
	if (str.len > 0)
		check_syntax_ins_arg(data, &str);
	if (str.len > 0)
		pwarn(data, P_ERR_MSG_INS_GARBAGE, str.str, str.len);
}
