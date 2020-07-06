/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_semantic.c                                   :+:      :+:    :+:   */
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
** check_semantic_txt_directives() - Check the semantic of textual directives
** @txt_directives: The textual directives to check
**
** Because of the line number constraints (25 by functions), this function and
** the ones it calls store a potential malloc error indicator in a t_check_data.
** If a malloc error is encountered with a ft_array_push() call,
** data->parsing_errors will be freed and set to NULL, which lets further
** ft_array_push() calls fail properly.
**
** Return: On success a t_array* of t_parse_error. On malloc error NULL.
*/

t_array	*check_semantic_txt_directives(t_array *txt_directives)
{
	size_t			i;
	t_txt_ins		*txt_ins;
	t_check_data	data;

	if (!(data.parsing_errors = ft_array_new(sizeof(t_parse_error), NULL)))
		return (NULL);
	i = 0;
	while ((txt_ins = txt_directives_get_ins(&data, txt_directives, i)))
	{
		check_semantic_txt_ins(&data, *txt_ins);
		i++;
	}
	check_semantic_txt_directives_ins_labels(&data, txt_directives);
	check_semantic_txt_directives_meta(&data, txt_directives);
	return (data.parsing_errors);
}
