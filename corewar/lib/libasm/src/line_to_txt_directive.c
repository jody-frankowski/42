/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_txt_directive.c                            :+:      :+:    :+:   */
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
** line_to_txt_directive() - Convert a line to a textual metadata or instruction
**                           directive
** @line:     The line to convert
** @line_num: The line number of @line
**
** Return: A txt_meta or a txt_ins in a t_directive tagged union.
*/

t_txt_directive	line_to_txt_directive(t_bstr line)
{
	t_txt_directive	directive;

	line = bstr_read_until(&line, COMMENT_CHARS);
	line = bstr_trim(line, WSP);
	if (line.len == 0)
	{
		directive.type = TXT_DIRECTIVE_TYPE_NONE;
		return (directive);
	}
	if (line.str[0] == '.' || ft_memchr(line.str, '"', line.len))
	{
		directive.type = TXT_DIRECTIVE_TYPE_META;
		directive.directive.meta = txt_to_txt_meta(line);
		return (directive);
	}
	else
	{
		directive.type = TXT_DIRECTIVE_TYPE_INS;
		directive.directive.ins = txt_to_txt_ins(line);
		return (directive);
	}
}
