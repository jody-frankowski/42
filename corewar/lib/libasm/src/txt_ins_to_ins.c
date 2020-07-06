/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_ins_to_ins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

static void	ins_set_instruction(t_ins *ins, t_bstr name)
{
	size_t	i;

	ins->instruction = NULL;
	i = 0;
	while (i < INSTRUCTIONS_COUNT)
	{
		if (bstr_cmp(str_to_bstr(g_instructions[i].mnemonic), name) == 0)
		{
			ins->instruction = &(g_instructions[i]);
			return ;
		}
		i++;
	}
}

static void	ins_set_args(t_ins *ins, t_txt_ins *txt_ins)
{
	char	str[DIRECT_VALUE_MAX_LEN + 1];
	size_t	i;
	t_bstr	arg;

	i = 0;
	while (i < txt_ins->args_count)
	{
		arg = txt_ins->args[i];
		if (bstr_skip_char(&arg, REGISTER_CHAR[0]))
			ins->args_type[i] = REG_ARG;
		else if (bstr_skip_char(&arg, DIRECT_VALUE_CHAR[0]))
			ins->args_type[i] = DIR_ARG;
		else
			ins->args_type[i] = IND_ARG;
		if (ins->args_type[i] == REG_ARG || ((ins->args_type[i] == DIR_ARG ||
			ins->args_type[i] == IND_ARG) &&
			!bstr_skip_char(&arg, LABEL_CHAR[0])))
		{
			ft_memcpy(str, arg.str, arg.len);
			str[arg.len] = '\0';
			ins->args[i] = (uint32_t)ft_strtol(str, NULL, 10);
		}
		i++;
	}
}

/*
** txt_ins_to_ins() - Convert a txt_ins to an ins
** @txt_ins: The txt_ins to convert
**
** /!\ @txt_ins must be free of errors.
** /!\ If there are label references in the arguments, directives_fill_labels()
** needs to be called after this function if the caller wants the labels to be
** filled.
**
** If @txt_ins only contains a label, the ins returned will have its instruction
** member set to NULL.
**
** Return: The corresponding ins.
*/

t_ins		txt_ins_to_ins(t_txt_ins txt_ins)
{
	t_ins	ins;

	ft_bzero(&ins, sizeof(t_ins));
	ins_set_instruction(&ins, txt_ins.name);
	ins_set_args(&ins, &txt_ins);
	ins_set_size(&ins);
	return (ins);
}
