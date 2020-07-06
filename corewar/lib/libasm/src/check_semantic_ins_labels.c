/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_semantic_ins_labels.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libasm.h"
#include "libft.h"

static t_bstr	txt_ins_get_label(t_txt_ins *txt_ins, size_t index)
{
	size_t	label_index;
	size_t	i;

	label_index = 0;
	i = 0;
	while (i < txt_ins->args_count)
	{
		if (txt_ins_arg_has_label_reference(txt_ins->args[i]))
		{
			if (index == label_index)
				return (txt_ins_arg_get_label(txt_ins->args[i]));
			else
				label_index++;
		}
		i++;
	}
	return ((t_bstr){.str = NULL, .len = 0});
}

static bool		check_labels_duplicate(t_check_data *data,
										t_array *txt_directives,
										t_array *found)
{
	t_txt_ins	*txt_ins;
	size_t		i;
	t_bstr		label;

	i = 0;
	while ((txt_ins = txt_directives_get_ins(data, txt_directives, i)))
	{
		label = txt_ins->label;
		if (bstr_cmp(label, str_to_bstr("")) != 0)
		{
			if (bstr_array_is_in(found, label))
				perr(data, P_ERR_MSG_INS_LABEL_DUPLICATE, label.str, label.len);
			else
			{
				if (!bstr_array_add(found, label))
					return (false);
			}
		}
		i++;
	}
	return (true);
}

static bool		check_labels_unknown(t_check_data *data,
											t_array *txt_directives,
											t_array *found,
											t_array *used)
{
	t_txt_ins	*txt_ins;
	size_t		i;
	size_t		j;
	t_bstr		label;

	i = 0;
	while ((txt_ins = txt_directives_get_ins(data, txt_directives, i)))
	{
		j = 0;
		while ((label = txt_ins_get_label(txt_ins, j)).str)
		{
			if (!bstr_array_is_in(found, label))
				perr(data, P_ERR_MSG_INS_LABEL_UNKNOWN, label.str, label.len);
			else
			{
				if (!bstr_array_add(used, label))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

static bool		check_labels_unused(t_check_data *data,
										t_array *txt_directives,
										t_array *used)
{
	t_txt_ins	*txt_ins;
	size_t		i;
	t_bstr		label;

	i = 0;
	while ((txt_ins = txt_directives_get_ins(data, txt_directives, i)))
	{
		label = txt_ins->label;
		if (bstr_cmp(label, str_to_bstr("")) != 0)
		{
			if (!bstr_array_is_in(used, label))
				pwarn(data, P_ERR_MSG_INS_LABEL_UNUSED, label.str, label.len);
		}
		i++;
	}
	return (true);
}

/*
** check_semantic_txt_directives_ins_labels() - Check the semantic of textual
**                                              instruction directives
** @data:           The current check_data
** @txt_directives: The array of textual directives
**
** Return: On success true. On malloc error false.
*/

bool			check_semantic_txt_directives_ins_labels(t_check_data *data,
														t_array *txt_directives)
{
	t_array	*found;
	t_array	*used;

	found = NULL;
	used = NULL;
	if (!(found = ft_array_new(sizeof(t_bstr), NULL)))
		return (bstr_array_free(found, used));
	if (!(used = ft_array_new(sizeof(t_bstr), NULL)))
		return (bstr_array_free(found, used));
	if (!check_labels_duplicate(data, txt_directives, found))
		return (bstr_array_free(found, used));
	if (!check_labels_unknown(data, txt_directives, found, used))
		return (bstr_array_free(found, used));
	if (!check_labels_unused(data, txt_directives, used))
		return (bstr_array_free(found, used));
	bstr_array_free(found, used);
	return (true);
}
