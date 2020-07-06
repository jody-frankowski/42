/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_semantic_txt_ins_arg.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libasm.h"
#include "libft.h"

static long	get_bstr_value(t_bstr arg)
{
	char	str[DIRECT_VALUE_MAX_LEN + 1];

	ft_memcpy(str, arg.str, arg.len);
	str[arg.len] = '\0';
	return (ft_strtol(str, NULL, 10));
}

/*
** This function assumes a 64-bit architecture with int being 32 bits long.
*/

static void	check_txt_ins_arg_type_direct(t_check_data *data,
												t_ins_spec *ins_spec,
												t_bstr arg)
{
	long	value;

	if (bstr_skip_char(&arg, LABEL_CHAR[0]))
		return ;
	value = get_bstr_value(arg);
	if (ins_spec->direct_arg_size == 4)
	{
		if (value < INT_MIN)
			perr(data, P_ERR_MSG_INS_VAL_INT_MIN, arg.str, arg.len);
		if (value > INT_MAX)
			perr(data, P_ERR_MSG_INS_VAL_INT_MAX, arg.str, arg.len);
	}
	else
	{
		if (value < SHRT_MIN)
			perr(data, P_ERR_MSG_INS_VAL_SHRT_MIN, arg.str, arg.len);
		if (value > SHRT_MAX)
			perr(data, P_ERR_MSG_INS_VAL_SHRT_MAX, arg.str, arg.len);
	}
}

static void	check_txt_ins_arg_type_indirect(t_check_data *data,
												t_bstr arg)
{
	long	value;

	if (bstr_skip_char(&arg, LABEL_CHAR[0]))
		return ;
	value = get_bstr_value(arg);
	if (value < SHRT_MIN)
		perr(data, P_ERR_MSG_INS_VAL_SHRT_MIN, arg.str, arg.len);
	if (value > SHRT_MAX)
		perr(data, P_ERR_MSG_INS_VAL_SHRT_MAX, arg.str, arg.len);
}

static void	check_txt_ins_arg_type_register(t_check_data *data,
												t_bstr arg)
{
	long	value;

	if (bstr_skip_char(&arg, LABEL_CHAR[0]))
		return ;
	value = get_bstr_value(arg);
	if (value < 1 || value > REGISTERS_COUNT)
		perr(data, P_ERR_MSG_INS_INVALID_REGISTER, arg.str, arg.len);
}

void		check_txt_ins_arg(t_check_data *data,
								t_ins_spec *ins_spec,
								t_bstr arg,
								size_t i)
{
	if (bstr_skip_char(&arg, DIRECT_VALUE_CHAR[0]))
	{
		if (!(ins_spec->args_types[i] & DIR_ARG_BIT))
			perr(data, P_ERR_MSG_INS_FORBID_DIR_ARG, arg.str - 1, arg.len + 1);
		else
			check_txt_ins_arg_type_direct(data, ins_spec, arg);
	}
	else if (bstr_skip_char(&arg, REGISTER_CHAR[0]))
	{
		if (!(ins_spec->args_types[i] & REG_ARG_BIT))
			perr(data, P_ERR_MSG_INS_FORBID_REG_ARG, arg.str - 1, arg.len + 1);
		else
			check_txt_ins_arg_type_register(data, arg);
	}
	else
	{
		if (!(ins_spec->args_types[i] & IND_ARG_BIT))
			perr(data, P_ERR_MSG_INS_FORBID_IND_ARG, arg.str, arg.len);
		else
			check_txt_ins_arg_type_indirect(data, arg);
	}
}
