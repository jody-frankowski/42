/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_meta.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include "libft.h"

static void	check_name(t_check_data *data, t_bstr *str)
{
	size_t	count;
	t_bstr	name;

	count = bstr_skip_char(str, META_DIRECTIVE_CHAR[0]);
	if (count == 0)
		pwarn(data, P_ERR_MSG_META_MISS_DOT, str->str, 0);
	name = bstr_read_until(str, WSP""META_QUOTE_CHAR);
	check_syntax_charset(data, name, META_NAME_CHARSET);
	if (name.len == 0)
		perr(data, P_ERR_MSG_META_MISS_NAME, str->str, 0);
}

static void	check_value(t_check_data *data, t_bstr *str)
{
	size_t	count;

	count = bstr_skip_char(str, META_QUOTE_CHAR[0]);
	if (count == 0)
		pwarn(data, P_ERR_MSG_META_MISS_OPEN_QUOTE, str->str, 0);
	bstr_read_until(str, META_QUOTE_CHAR);
	count = bstr_skip_char(str, META_QUOTE_CHAR[0]);
	if (count == 0)
		pwarn(data, P_ERR_MSG_META_MISS_CLOSE_QUOTE, str->str, 0);
}

void		check_syntax_meta(t_check_data *data, t_bstr str)
{
	size_t	count;

	check_name(data, &str);
	if (str.len == 0)
	{
		pwarn(data, P_ERR_MSG_META_MISS_VALUE, str.str, 0);
		return ;
	}
	count = bstr_skip_chars(&str, WSP);
	if (count == 0)
		pwarn(data, P_ERR_MSG_META_MISS_WSP_BETWEEN_NAME_AND_VALUE, str.str, 0);
	check_value(data, &str);
	if (str.len > 0)
		pwarn(data, P_ERR_MSG_META_GARBAGE, str.str, str.len);
}
