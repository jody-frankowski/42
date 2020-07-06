/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:10:44 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/27 01:55:58 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		init_instruction(t_process *browse)
{
	browse->current_instruction = (t_ins){NULL, {0, 0, 0}, {0, 0, 0}, 0};
}

/*
** get_opcode() - Get opcode at current position
** @arena: The arena
** @browse: The current process
**
** Get opcode at the process position
*/

void		get_opcode(t_arena *arena, t_process *browse)
{
	char	opcode;

	opcode = arena->memory[browse->pc].value;
	if (opcode >= 1 && opcode <= INSTRUCTIONS_COUNT)
		browse->current_instruction.instruction = &(g_instructions[opcode - 1]);
	if (browse->current_instruction.instruction != NULL)
		browse->instruction_end =
			arena->cycle + browse->current_instruction.instruction->num_cycles;
	else
		browse->instruction_end = arena->cycle + 1;
}

/*
** get_ins_args() - Get instruction args
** @ins: A pointer to the ins to modify
** @bin: Buffer to read from
**
** Get current instruction args.
*/

void		get_ins_args(t_ins *ins, char *bin)
{
	size_t	j;

	ins_set_args_type(ins, &bin);
	if (ins->instruction->has_acb && !ins_args_ok(ins))
	{
		*ins = (t_ins){NULL, {0, 0, 0}, {0, 0, 0}, 0};
		return ;
	}
	j = 0;
	while (j < ins->instruction->num_args)
	{
		if (!ins_set_arg(ins, j, &bin))
		{
			*ins = (t_ins){NULL, {0, 0, 0}, {0, 0, 0}, 0};
			return ;
		}
		j++;
	}
	ins_set_size(ins);
	return ;
}

/*
** get_instruction() - Read next instruction
** @arena: The arena
** @browse: The current process
**
** Reads the instruction at the process position
*/

void		get_instruction(t_arena *arena, t_process *browse)
{
	char	instruction[INS_MAX_SIZE];
	int		index;
	int		pc;
	int		size;

	index = 0;
	ft_bzero(instruction, INS_MAX_SIZE * sizeof(char));
	pc = browse->pc;
	while (index < INS_MAX_SIZE)
	{
		if (pc >= MEM_SIZE)
			pc = 0;
		instruction[index] = arena->memory[pc].value;
		index++;
		pc++;
	}
	get_ins_size(&browse->current_instruction, &instruction[1]);
	size = browse->current_instruction.size;
	get_ins_args(&browse->current_instruction, &instruction[1]);
	if (browse->current_instruction.instruction == NULL)
		browse->current_instruction.size = size;
}
