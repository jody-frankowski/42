/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_to_txt_ins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include "libft.h"

/*
** get_arg() - Get an operand from a bstr
** @str: The bstr to read from
**
** Return: The operand in a bstr.
*/

static t_bstr		get_arg(t_bstr *str)
{
	t_bstr	arg;

	bstr_skip_chars(str, WSP);
	bstr_skip_char(str, OPERANDS_SEPARATOR_CHAR[0]);
	bstr_skip_chars(str, WSP);
	arg = bstr_read_until(str, WSP""OPERANDS_SEPARATOR_CHAR);
	return (arg);
}

/*
** txt_to_txt_ins() - Convert a bstr to a txt_ins
** @txt: The bstr to convert
**
** @txt must be free of syntax errors (eg. Missing whitespace/comma).
**
** Return: The converted txt_ins
*/

t_txt_ins			txt_to_txt_ins(t_bstr txt)
{
	t_txt_ins	txt_ins;
	t_bstr		str;

	ft_bzero(&txt_ins, sizeof(txt_ins));
	str = bstr_read_until(&txt, WSP""LABEL_CHAR);
	if (bstr_skip_char(&txt, LABEL_CHAR[0]))
	{
		txt_ins.label = str;
		bstr_skip_chars(&txt, WSP);
		txt_ins.name = bstr_read_until(&txt, WSP);
	}
	else
		txt_ins.name = str;
	bstr_skip_chars(&txt, WSP);
	txt_ins.args_count = 0;
	if (txt.len > 0)
		txt_ins.args[txt_ins.args_count++] =
			bstr_read_until(&txt, WSP""OPERANDS_SEPARATOR_CHAR);
	if (txt.len > 0)
		txt_ins.args[txt_ins.args_count++] = get_arg(&txt);
	if (txt.len > 0)
		txt_ins.args[txt_ins.args_count++] = get_arg(&txt);
	return (txt_ins);
}
