/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_directives_get.c                               :+:      :+:    :+:   */
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
** txt_directives_get_ins() - Get a txt_ins from an array of txt_directives
** @data:           The check_data to modify if it isn't NULL
** @txt_directives: The array of txt_directives
** @index:          The index of the t_ins to get
**
** @data can be NULL if the caller doesn't need to modify its check_data.
**
** Return: A pointer to the txt_ins on success. NULL on error.
*/

t_txt_ins	*txt_directives_get_ins(t_check_data *data,
											t_array *txt_directives,
											size_t index)
{
	size_t			i;
	size_t			txt_ins_index;
	t_txt_directive	*txt_directive;

	i = 0;
	txt_ins_index = 0;
	while (i < txt_directives->len)
	{
		txt_directive = ft_array_get(txt_directives, i);
		if (txt_directive->type == TXT_DIRECTIVE_TYPE_INS)
		{
			if (txt_ins_index == index)
			{
				if (data)
				{
					data->line = txt_directive->line;
					data->line_num = txt_directive->line_num;
				}
				return (&txt_directive->directive.ins);
			}
			txt_ins_index++;
		}
		i++;
	}
	return (NULL);
}

/*
** txt_directives_get_meta() - Get a txt_meta from an array of txt_directives
** @data:           The check_data to modify if it isn't NULL
** @txt_directives: The array of txt_directives
** @index:          The index of the t_meta to get
**
** @data can be NULL if the caller doesn't need to modify its check_data.
**
** Return: A pointer to the txt_meta on success. NULL on error.
*/

t_txt_meta	*txt_directives_get_meta(t_check_data *data,
									t_array *txt_directives,
									size_t index)
{
	size_t			i;
	size_t			txt_meta_index;
	t_txt_directive	*txt_directive;

	i = 0;
	txt_meta_index = 0;
	while (i < txt_directives->len)
	{
		txt_directive = ft_array_get(txt_directives, i);
		if (txt_directive->type == TXT_DIRECTIVE_TYPE_META)
		{
			if (txt_meta_index == index)
			{
				if (data)
				{
					data->line = txt_directive->line;
					data->line_num = txt_directive->line_num;
				}
				return (&txt_directive->directive.meta);
			}
			txt_meta_index++;
		}
		i++;
	}
	return (NULL);
}
