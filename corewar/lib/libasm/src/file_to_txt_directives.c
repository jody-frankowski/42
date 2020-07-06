/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_txt_directives.c                           :+:      :+:    :+:   */
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

/*
** file_to_txt_directives() - Convert a file to textual metadata and instruction
**                            directives
** @file: The file to convert
**
** Return: On success a pointer to a t_array, on error NULL.
*/

t_array	*file_to_txt_directives(t_bstr file)
{
	t_array			*txt_directives;
	size_t			line_num;
	t_bstr			line;
	t_txt_directive	directive;

	txt_directives = ft_array_new(sizeof(t_txt_directive), NULL);
	if (!txt_directives)
		return (NULL);
	line_num = 1;
	while (file.len > 0)
	{
		line = bstr_read_until(&file, "\n");
		directive = line_to_txt_directive(line);
		directive.line = line;
		directive.line_num = line_num;
		if (directive.type != TXT_DIRECTIVE_TYPE_NONE)
			if (!ft_array_push(txt_directives, &directive))
				return (ft_array_free(txt_directives));
		line_num++;
		bstr_skip_char(&file, '\n');
	}
	return (txt_directives);
}
