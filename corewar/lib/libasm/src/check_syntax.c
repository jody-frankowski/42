/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include "libft.h"

void	check_syntax_charset(t_check_data *data, t_bstr str, char *charset)
{
	size_t	i;

	i = 0;
	while (i < str.len)
	{
		if (!ft_incharset(str.str[i], charset))
			perr(data, P_ERR_MSG_FORBIDDEN_CHAR, &str.str[i], 1);
		i++;
	}
}

void	check_syntax_line(t_check_data *data, t_bstr line)
{
	data->line = line;
	line = bstr_read_until(&line, COMMENT_CHARS);
	line = bstr_trim(line, WSP);
	if (line.len == 0)
		return ;
	if (line.str[0] == '.' || ft_memchr(line.str, '"', line.len))
		check_syntax_meta(data, line);
	else
		check_syntax_ins(data, line);
}

/*
** check_syntax_file() - Check the syntax of a file
** @file: The file to check
**
** Return: A t_array* of errors on success. NULL on malloc error.
*/

t_array	*check_syntax_file(t_bstr file)
{
	t_bstr			line;
	t_check_data	data;

	if (!(data.parsing_errors = ft_array_new(sizeof(t_parse_error), NULL)))
		return (NULL);
	data.line_num = 1;
	while (file.len > 0)
	{
		line = bstr_read_until(&file, "\n");
		check_syntax_line(&data, line);
		data.line_num++;
		bstr_skip_char(&file, '\n');
	}
	return (data.parsing_errors);
}
