/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_to_txt_meta.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

/*
** txt_to_txt_meta() - Convert a bstr to a txt_meta
** @txt: The bstr to convert
**
** @txt must be free of syntax errors (eg. Missing quotes).
**
** Return: The converted txt_meta
*/

t_txt_meta	txt_to_txt_meta(t_bstr txt)
{
	t_txt_meta	txt_meta;

	ft_bzero(&txt_meta, sizeof(txt_meta));
	bstr_skip_char(&txt, META_DIRECTIVE_CHAR[0]);
	txt_meta.name = bstr_read_until(&txt, WSP""META_QUOTE_CHAR);
	bstr_skip_chars(&txt, WSP);
	bstr_skip_char(&txt, META_QUOTE_CHAR[0]);
	txt_meta.value = bstr_read_until(&txt, META_QUOTE_CHAR);
	bstr_skip_char(&txt, META_QUOTE_CHAR[0]);
	return (txt_meta);
}
