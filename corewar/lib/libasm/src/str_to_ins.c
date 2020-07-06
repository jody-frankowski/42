/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_ins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

/*
** str_to_ins() - Convert a string to an ins
** @str: The string to convert
**
** /!\ @str must be free of errors.
**
** Return: The corresponding t_ins.
*/

t_ins	str_to_ins(char *str)
{
	return (txt_ins_to_ins(txt_to_txt_ins(str_to_bstr(str))));
}
