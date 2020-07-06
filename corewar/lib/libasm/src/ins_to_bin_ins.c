/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_to_bin_ins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

static void	set_acb(t_bin_ins *bin_ins, t_ins *ins, size_t *i)
{
	size_t	j;

	if (ins->instruction->has_acb)
	{
		bin_ins->bin[*i] = 0;
		j = 0;
		while (j < ins->instruction->num_args)
		{
			bin_ins->bin[*i] |= ins->args_type[j] << (6 - (2 * j));
			j++;
		}
		(*i)++;
	}
}

static void	set_register_arg(t_bin_ins *bin_ins,
								t_ins *ins,
								size_t *i,
								size_t *j)
{
	bin_ins->bin[*i] = (uint8_t)ins->args[*j];
	*i += REG_ARG_SIZE;
}

static void	set_direct_arg(t_bin_ins *bin_ins, t_ins *ins, size_t *i, size_t *j)
{
	uint32_t	converted;

	if (ins->instruction->direct_arg_size == 2)
		converted = ft_htobe16(ins->args[*j]);
	else
		converted = ft_htobe32(ins->args[*j]);
	ft_memcpy(bin_ins->bin + *i, &converted, ins->instruction->direct_arg_size);
	*i += ins->instruction->direct_arg_size;
}

static void	set_indirect_arg(t_bin_ins *bin_ins,
								t_ins *ins,
								size_t *i,
								size_t *j)
{
	uint32_t	converted;

	converted = ft_htobe16(ins->args[*j]);
	ft_memcpy(bin_ins->bin + *i, &converted, IND_ARG_SIZE);
	*i += IND_ARG_SIZE;
}

/*
** ins_to_bin_ins() - Convert a t_ins to a t_bin_ins
** @ins: The instruction to convert
**
** Return: The corresponding t_bin_ins. If @ins is a label-only instruction
**         (@ins->instruction == NULL), t_bin_ins.bin[0] will be equal to 0.
*/

t_bin_ins	ins_to_bin_ins(t_ins *ins)
{
	size_t		i;
	size_t		j;
	t_bin_ins	bin_ins;

	ft_bzero(&bin_ins, sizeof(bin_ins));
	if (!ins->instruction)
		return (bin_ins);
	i = 0;
	bin_ins.bin[i] = ins->instruction->opcode;
	i++;
	set_acb(&bin_ins, ins, &i);
	j = 0;
	while (j < ins->instruction->num_args)
	{
		if (ins->args_type[j] == REG_ARG)
			set_register_arg(&bin_ins, ins, &i, &j);
		else if (ins->args_type[j] == DIR_ARG)
			set_direct_arg(&bin_ins, ins, &i, &j);
		else if (ins->args_type[j] == IND_ARG)
			set_indirect_arg(&bin_ins, ins, &i, &j);
		j++;
	}
	bin_ins.len = i;
	return (bin_ins);
}
