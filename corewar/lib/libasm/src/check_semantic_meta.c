/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_semantic_meta.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include "libft.h"

static void	check_length(t_check_data *data, t_txt_meta *txt_meta)
{
	if (bstr_cmp(txt_meta->name, str_to_bstr(META_DIRECTIVE_NAME)) == 0)
	{
		if (txt_meta->value.len > PROG_NAME_LENGTH)
			pwarn(data, P_ERR_MSG_META_TOO_LONG_NAME_DIRECTIVE,
					txt_meta->value.str, txt_meta->value.len);
	}
	if (bstr_cmp(txt_meta->name, str_to_bstr(META_DIRECTIVE_COMMENT)) == 0)
	{
		if (txt_meta->value.len > PROG_COMMENT_LENGTH)
			pwarn(data, P_ERR_MSG_META_TOO_LONG_COMMENT_DIRECTIVE,
					txt_meta->value.str, txt_meta->value.len);
	}
}

static bool	check_duplicate(t_check_data *data, t_array *found, t_bstr name)
{
	if (bstr_array_is_in(found, name))
		pwarn(data, P_ERR_MSG_META_DIRECTIVE_DUPLICATE, name.str, name.len);
	else
	{
		if (!bstr_array_add(found, name))
			return (false);
	}
	return (true);
}

static void	check_missing_name_and_comment(t_check_data *data,
												t_array *found)
{
	if (!bstr_array_is_in(found, str_to_bstr(META_DIRECTIVE_NAME)))
		pwarn(data, P_ERR_MSG_META_MISS_DIRECTIVE_NAME, NULL, 0);
	if (!bstr_array_is_in(found, str_to_bstr(META_DIRECTIVE_COMMENT)))
		pwarn(data, P_ERR_MSG_META_MISS_DIRECTIVE_COMMENT, NULL, 0);
}

/*
** check_semantic_txt_directives_meta() - Check the semantic of textual
**                                        metadata directives
** @data:           The current check_data
** @txt_directives: The array of textual directives
**
** Return: On success true. On malloc error false.
*/

bool		check_semantic_txt_directives_meta(t_check_data *data,
												t_array *txt_directives)
{
	t_array		*found;
	size_t		i;
	t_txt_meta	*txt_meta;

	if (!(found = ft_array_new(sizeof(t_bstr), NULL)))
		return (false);
	i = 0;
	while ((txt_meta = txt_directives_get_meta(data, txt_directives, i)))
	{
		if (bstr_cmp(txt_meta->name, str_to_bstr(META_DIRECTIVE_NAME)) != 0 &&
			bstr_cmp(txt_meta->name, str_to_bstr(META_DIRECTIVE_COMMENT)) != 0)
			pwarn(data, P_ERR_MSG_META_DIRECTIVE_UNKNOWN,
					txt_meta->name.str, txt_meta->name.len);
		else
		{
			check_length(data, txt_meta);
			if (!check_duplicate(data, found, txt_meta->name))
				return (ft_array_free(found));
		}
		i++;
	}
	check_missing_name_and_comment(data, found);
	ft_array_free(found);
	return (true);
}
