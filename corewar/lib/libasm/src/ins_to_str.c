/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_to_str.c                                       :+:      :+:    :+:   */
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
#include "libprintf.h"

/*
** ins_to_str() - Convert an ins to a string
** @ins: The instruction to use
**
** str buffer size explanation:
** - 5 chars for the mnemonic
** - 1 space char
** - 12 chars for a '%' char an optional '-' char plus 10 chars for values up to
**   2,147,483,648
** - 2 chars for ", "
** - 12 chars for a '%' char an optional '-' char plus 10 chars for values up to
**   2,147,483,648
** - 2 chars for ", "
** - 12 chars for a '%' char an optional '-' char plus 10 chars for values up to
**   2,147,483,648
** - 1 last char for the null byte
**
** Return: A pointer to a static buffer containing the representation, ending
** with a null byte.
*/

char	*ins_to_str(t_ins ins)
{
	static char	str[5 + 1 + 12 + 2 + 12 + 2 + 12 + 1];
	size_t		i;

	str[0] = '\0';
	if (!ins.instruction)
		return (str);
	ft_strcpy(str, ins.instruction->mnemonic);
	ft_strcat(str, " ");
	i = 0;
	while (i < ins.instruction->num_args)
	{
		if (i > 0)
			ft_strcat(str, OPERANDS_SEPARATOR_CHAR" ");
		if (ins.args_type[i] == REG_ARG)
			ft_strcat(str, REGISTER_CHAR);
		if (ins.args_type[i] == DIR_ARG)
			ft_strcat(str, DIRECT_VALUE_CHAR);
		ft_sprintf(str + ft_strlen(str), "%d", ins.args[i]);
		i++;
	}
	return (str);
}
