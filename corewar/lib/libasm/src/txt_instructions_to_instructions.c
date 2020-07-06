/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_instructions_to_instructions.c                 :+:      :+:    :+:   */
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

static int32_t	label_get_offset(t_bstr label,
									t_array *txt_directives,
									t_array *instructions,
									size_t index)
{
	size_t		i;
	int32_t		offset;
	t_txt_ins	*txt_ins;

	offset = 0;
	i = index;
	while ((txt_ins = txt_directives_get_ins(NULL, txt_directives, i)))
	{
		if (bstr_cmp(label, txt_ins->label) == 0)
			return (offset);
		offset += ((t_ins*)ft_array_get(instructions, i))->size;
		i++;
	}
	offset = ((t_ins*)ft_array_get(instructions, index))->size;
	i = index + 1;
	while (i != 0)
	{
		i--;
		txt_ins = txt_directives_get_ins(NULL, txt_directives, i);
		offset -= ((t_ins*)ft_array_get(instructions, i))->size;
		if (bstr_cmp(label, txt_ins->label) == 0)
			return (offset);
	}
	return (offset);
}

static void		instructions_fill_labels(t_array *txt_directives,
												t_array *instructions)
{
	size_t			i;
	size_t			j;
	t_txt_ins		*txt_ins;
	t_ins			*ins;

	i = 0;
	while ((txt_ins = txt_directives_get_ins(NULL, txt_directives, i)))
	{
		ins = ft_array_get(instructions, i);
		j = 0;
		while (j < txt_ins->args_count)
		{
			if (txt_ins_arg_has_label_reference(txt_ins->args[j]))
				ins->args[j] =
					label_get_offset(txt_ins_arg_get_label(txt_ins->args[j]),
										txt_directives, instructions, i);
			j++;
		}
		i++;
	}
}

t_array			*txt_instructions_to_instructions(t_array *txt_directives)
{
	t_array		*instructions;
	size_t		i;
	t_txt_ins	*txt_ins;
	t_ins		ins;

	instructions = ft_array_new(sizeof(t_ins), NULL);
	if (!instructions)
		return (NULL);
	i = 0;
	while ((txt_ins = txt_directives_get_ins(NULL, txt_directives, i)))
	{
		ins = txt_ins_to_ins(*txt_ins);
		if (!ft_array_push(instructions, &ins))
			return (ft_array_free(instructions));
		i++;
	}
	instructions_fill_labels(txt_directives, instructions);
	return (instructions);
}
