/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_ins_arg.c                                      :+:      :+:    :+:   */
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
** txt_ins_arg_get_label() - Get a label from a txt_ins arg
** @arg: The argument to get the label from
**
** txt_ins_arg_has_label_reference() should be called before to make sure the
** argument has a label reference.
**
** Return: A t_bst containing the label reference (without LABEL_CHAR).
*/

t_bstr	txt_ins_arg_get_label(t_bstr arg)
{
	bstr_skip_char(&arg, DIRECT_VALUE_CHAR[0]);
	bstr_skip_char(&arg, LABEL_CHAR[0]);
	return (arg);
}

/*
** txt_ins_arg_has_label_reference() - Check if a txt_ins arg has a label ref
** @arg: The argument to check
**
** Return: true if the argument contains a label ref, else false.
*/

bool	txt_ins_arg_has_label_reference(t_bstr arg)
{
	return (bstr_ncmp(arg, str_to_bstr(":"), 1) == 0 ||
			bstr_ncmp(arg, str_to_bstr("%:"), 2) == 0);
}
