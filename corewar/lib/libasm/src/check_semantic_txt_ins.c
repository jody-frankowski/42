/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_semantic_txt_ins.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libasm.h"
#include "libft.h"

static size_t	args_strlen(t_txt_ins txt_ins)
{
	if (txt_ins.args_count > 0)
		return (txt_ins.args[txt_ins.args_count - 1].str
				+ txt_ins.args[txt_ins.args_count - 1].len
				- (txt_ins.name.str + txt_ins.name.len));
	else
		return (0);
}

/*
** check_semantic_txt_ins() - Check the semantic of a txt_ins
** @data:    The current check_data
** @txt_ins: The txt_ins to check
*/

void			check_semantic_txt_ins(t_check_data *data, t_txt_ins txt_ins)
{
	t_ins_spec	*ins_spec;
	size_t		i;
	t_bstr		arg;

	if (txt_ins.name.len == 0)
		return ;
	if (!(ins_spec = txt_ins_get_ins_spec(txt_ins)))
	{
		perr(data, P_ERR_MSG_INS_UNKNOWN, txt_ins.name.str, txt_ins.name.len);
		return ;
	}
	if (txt_ins.args_count != ins_spec->num_args)
	{
		perr(data, P_ERR_MSG_INS_WRONG_OPERANDS_COUNT,
				txt_ins.name.str + txt_ins.name.len, args_strlen(txt_ins));
		return ;
	}
	i = 0;
	while (i < ins_spec->num_args)
	{
		arg = txt_ins.args[i];
		check_txt_ins_arg(data, ins_spec, arg, i);
		i++;
	}
}
