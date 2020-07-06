/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_ins_get_ins_spec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

/*
** txt_ins_get_ins_spec() - Get the ins_spec of a txt_ins
** @txt_ins: The textual instruction to use
**
** Return: A pointer to the corresponding ins_spec on success. NULL on error.
*/

t_ins_spec	*txt_ins_get_ins_spec(t_txt_ins txt_ins)
{
	size_t	i;

	i = 0;
	while (i < INSTRUCTIONS_COUNT)
	{
		if (bstr_cmp(txt_ins.name, str_to_bstr(g_instructions[i].mnemonic))
			== 0)
			return (&g_instructions[i]);
		i++;
	}
	return (NULL);
}
