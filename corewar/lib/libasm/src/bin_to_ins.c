/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_to_ins.c                                       :+:      :+:    :+:   */
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
** ins_set_args_type() - Set the arguments type of a t_ins
** @ins: The instruction to modify
** @bin: The buffer in which the ACB will be, if needed
** @bin_index: The index at which to look for the ACB in @bin
**
** The original vm doesn't check if the ACB is filled or not past the arguments
** it needs to parse. We don't either.
** This function doesn't check that the arguments type match the ones the
** instruction can take.
*/

void	ins_set_args_type(t_ins *ins, char **bin)
{
	size_t	i;

	i = 0;
	if (ins->instruction->has_acb)
	{
		while (i < ins->instruction->num_args)
		{
			ins->args_type[i] = (**bin >> (6 - i * 2)) & 0x03;
			i++;
		}
		(*bin)++;
	}
	else
	{
		while (i < ins->instruction->num_args)
		{
			if (ins->instruction->args_types[i] & REG_ARG_BIT)
				ins->args_type[i] = REG_ARG;
			if (ins->instruction->args_types[i] & DIR_ARG_BIT)
				ins->args_type[i] = DIR_ARG;
			if (ins->instruction->args_types[i] & IND_ARG_BIT)
				ins->args_type[i] = IND_ARG;
			i++;
		}
	}
}

/*
** ins_args_ok() - Check the validity of an instruction arguments
** @ins: The instruction to check
**
** Return: true if the arguments are valid, else false.
*/

bool	ins_args_ok(t_ins *ins)
{
	size_t	i;

	i = 0;
	while (i < ins->instruction->num_args)
	{
		if (ins->args_type[i] == NO_ARG ||
			(ins->args_type[i] == REG_ARG &&
			!(ins->instruction->args_types[i] & REG_ARG_BIT)) ||
			(ins->args_type[i] == DIR_ARG &&
			!(ins->instruction->args_types[i] & DIR_ARG_BIT)) ||
			(ins->args_type[i] == IND_ARG &&
			!(ins->instruction->args_types[i] & IND_ARG_BIT)))
			return (0);
		i++;
	}
	return (1);
}

/*
** ins_set_arg() - Set an instruction's argument
** @ins:     The instruction to modify
** @arg_num: The argument to read to
** @bin:     The buffer to read from
**
** Return: 1 if the argument is valid, otherwise 0
*/

int		ins_set_arg(t_ins *ins, size_t arg_num, char **bin)
{
	if (ins->args_type[arg_num] == DIR_ARG)
	{
		ft_memcpy(&ins->args[arg_num], *bin, ins->instruction->direct_arg_size);
		if (ins->instruction->direct_arg_size == 2)
			ins->args[arg_num] = ft_betoh16(ins->args[arg_num]);
		else
			ins->args[arg_num] = ft_betoh32(ins->args[arg_num]);
		*bin += ins->instruction->direct_arg_size;
	}
	else if (ins->args_type[arg_num] == IND_ARG)
	{
		ft_memcpy(&ins->args[arg_num], *bin, 2);
		ins->args[arg_num] = ft_betoh16(ins->args[arg_num]);
		*bin += 2;
	}
	else if (ins->args_type[arg_num] == REG_ARG)
	{
		ins->args[arg_num] = *(uint8_t*)(*bin);
		if (!(1 <= ins->args[arg_num] && ins->args[arg_num] <= 16))
			return (0);
		*bin += 1;
	}
	return (1);
}

/*
** bin_to_ins() - Read a t_ins from a binary stream
** @bin: The buffer to read from
**
** @bin is guaranteed to be as big as the biggest instruction and be padded on
** the right with zeroes, so there should be no worry of buffer over-read.
**
** Return: On success, an instatiated t_ins, else a t_ins filled with zeroes.
*/

t_ins	bin_to_ins(char bin[INS_MAX_SIZE])
{
	t_ins		ins;
	size_t		j;

	if (*bin < 1 || *bin > INSTRUCTIONS_COUNT)
		return ((t_ins){NULL, {0, 0, 0}, {0, 0, 0}, 0});
	ins.instruction = &(g_instructions[*bin - 1]);
	bin++;
	ins_set_args_type(&ins, &bin);
	if (ins.instruction->has_acb && !ins_args_ok(&ins))
		return ((t_ins){NULL, {0, 0, 0}, {0, 0, 0}, 0});
	j = 0;
	while (j < ins.instruction->num_args)
	{
		if (!ins_set_arg(&ins, j, &bin))
			return ((t_ins){NULL, {0, 0, 0}, {0, 0, 0}, 0});
		j++;
	}
	ins_set_size(&ins);
	return (ins);
}
