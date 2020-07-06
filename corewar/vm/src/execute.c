/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:10:37 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/27 02:16:45 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			which_instruction_2(t_arena *arena, t_process *process)
{
	if (process->current_instruction.instruction->opcode == 9)
		ins_zjmp(arena, process);
	else if (process->current_instruction.instruction->opcode == 10)
		ins_ldi(arena, process);
	else if (process->current_instruction.instruction->opcode == 11)
		ins_sti(arena, process);
	else if (process->current_instruction.instruction->opcode == 12)
		ins_fork(arena, process);
	else if (process->current_instruction.instruction->opcode == 13)
		ins_lld(arena, process);
	else if (process->current_instruction.instruction->opcode == 14)
		ins_lldi(arena, process);
	else if (process->current_instruction.instruction->opcode == 15)
		ins_lfork(arena, process);
	else if (process->current_instruction.instruction->opcode == 16)
		ins_aff(arena, process);
}

void			which_instruction(t_arena *arena, t_process *process)
{
	if (process->current_instruction.instruction->opcode == 1)
		ins_live(arena, process);
	else if (process->current_instruction.instruction->opcode == 2)
		ins_ld(arena, process);
	else if (process->current_instruction.instruction->opcode == 3)
		ins_st(arena, process);
	else if (process->current_instruction.instruction->opcode == 4)
		ins_add(arena, process);
	else if (process->current_instruction.instruction->opcode == 5)
		ins_sub(arena, process);
	else if (process->current_instruction.instruction->opcode == 6)
		ins_and(arena, process);
	else if (process->current_instruction.instruction->opcode == 7)
		ins_or(arena, process);
	else if (process->current_instruction.instruction->opcode == 8)
		ins_xor(arena, process);
	else
		which_instruction_2(arena, process);
}

/*
** execute_process() - Exec process
** @tmp: process to execute
** @save_inst_end: instruction end cycle
**
** execute process past in parameter
** Return: value of @save_inst_end
*/

int				execute_process(t_arena *arena, t_process *tmp,
	int save_inst_end)
{
	if (tmp->current_instruction.instruction == NULL)
	{
		get_opcode(arena, tmp);
		if (tmp->current_instruction.instruction == NULL)
			tmp->pc = (tmp->pc + 1) % MEM_SIZE;
		else
			tmp->instruction_end--;
	}
	if (tmp->instruction_end == (unsigned long)arena->cycle)
	{
		save_inst_end = tmp->instruction_end;
		get_instruction(arena, tmp);
		if (tmp->current_instruction.instruction != NULL)
			which_instruction(arena, tmp);
		tmp->instruction_end = save_inst_end;
		if (tmp->current_instruction.instruction == NULL ||
			tmp->current_instruction.instruction->opcode != 9)
			tmp->pc = (tmp->pc + tmp->current_instruction.size) % MEM_SIZE;
		init_instruction(tmp);
	}
	return (save_inst_end);
}

/*
** execute_all_processes() - Browse players and exec their processes
**
** browse processes and exec execute_process() for each of them
*/

void			execute_all_processes(t_arena *arena)
{
	t_process	*browse;
	int			save_inst_end;

	browse = arena->last_process;
	save_inst_end = 0;
	while (browse)
	{
		save_inst_end = execute_process(arena, browse, save_inst_end);
		browse = browse->prev;
	}
}
