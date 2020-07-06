/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libasm.h"
#include "libft.h"

/*
** ins_print() - Print an instruction in its textual representation
** @fd:  The file descriptor to print to
** @ins: The instruction to print
*/

void	ins_print(int fd, t_ins *ins)
{
	char *str;

	str = ins_to_str(*ins);
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}
