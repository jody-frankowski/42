/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarcher  <jarcher@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jarcher           #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jarcher          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include "vm.h"

void	test_ins_add()
{
	t_arena		arena;
	t_process	process;

	init_arena(&arena);
	init_process(&process, NULL, 0);
	init_instruction(&process);
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 0;
	process.current_instruction.args[1] = 3;
	process.current_instruction.args[2] = 2;

	// test avec tout à 0
	process.registers[0] = 0;
	process.registers[3] = 0;
	process.registers[2] = 0;
	ins_add(&arena, &process);
	ASSERT((int)process.registers[0], ==, 0);
	ASSERT((int)process.registers[3], ==, 0);
	ASSERT((int)process.registers[2], ==, 0);
	ASSERT((int)process.carry, ==, 1);

	// test que reg3 = reg1+reg2 et que carry = 0 si reg3 != 0
	process.registers[0] = 2;
	process.registers[3] = 5;
	process.registers[2] = 10;
	ins_add(&arena, &process);
	ASSERT((int)process.registers[0], ==, 2);
	ASSERT((int)process.registers[3], ==, 5);
	ASSERT((int)process.registers[2], ==, 7);
	ASSERT((int)process.carry, ==, 0);

	// test que reg3 = reg1+reg2 et que carry = 1 si reg3 == 0
	process.registers[0] = 5;
	process.registers[3] = -5;
	process.registers[2] = 10;
	ins_add(&arena, &process);
	ASSERT((int)process.registers[0], ==, 5);
	ASSERT((int)process.registers[3], ==, -5);
	ASSERT((int)process.registers[2], ==, 0);
	ASSERT((int)process.carry, ==, 1);
}

void	test_ins_and()
{
	t_arena		arena;
	t_process	process;

	init_arena(&arena);
	init_process(&process, NULL, 0);
	init_instruction(&process);

	// direct + direct + reg
	process.current_instruction.args_type[0] = DIR_ARG;
	process.current_instruction.args_type[1] = DIR_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 58;
	process.current_instruction.args[1] = 3;
	process.current_instruction.args[2] = 0;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 & 3));
	ASSERT((int)process.carry, ==, (58 & 3) == 0);

	process.current_instruction.args[0] = 69;
	process.current_instruction.args[1] = 11;
	process.current_instruction.args[2] = 0;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[0], ==, (69 & 11));
	ASSERT((int)process.carry, ==, (69 & 11) == 0);

	// direct + indirect + reg
	process.current_instruction.args_type[0] = DIR_ARG;
	process.current_instruction.args_type[1] = IND_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.pc = 0;
	process.current_instruction.args[0] = 58;
	process.current_instruction.args[1] = 10;
	process.current_instruction.args[2] = 0;
	arena.memory[10].value = 1;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 & 1));
	ASSERT((int)process.carry, ==, (58 & 1) == 0);

	arena.memory[10].value = 52;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 & 52));
	ASSERT((int)process.carry, ==, (58 & 52) == 0);

	// direct + reg + reg
	process.current_instruction.args_type[0] = DIR_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 58;
	process.current_instruction.args[1] = 1;
	process.current_instruction.args[2] = 0;
	process.registers[1] = 1;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 & 1));
	ASSERT((int)process.carry, ==, (58 & 1) == 0);

	process.current_instruction.args[1] = 3;
	process.registers[3] = 52;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 & 52));
	ASSERT((int)process.carry, ==, (58 & 52) == 0);

	// indirect + direct + reg
	process.current_instruction.args_type[0] = IND_ARG;
	process.current_instruction.args_type[1] = DIR_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.pc = 0;
	process.current_instruction.args[0] = 15;
	process.current_instruction.args[1] = 58;
	process.current_instruction.args[2] = 0;
	arena.memory[15].value = 1;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 & 1));
	ASSERT((int)process.carry, ==, (58 & 1) == 0);

	arena.memory[15].value = 52;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 & 52));
	ASSERT((int)process.carry, ==, (58 & 52) == 0);

	// indirect + indirect + reg
	process.current_instruction.args_type[0] = IND_ARG;
	process.current_instruction.args_type[1] = IND_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.pc = 0;
	process.current_instruction.args[0] = 15;
	process.current_instruction.args[1] = 17;
	process.current_instruction.args[2] = 0;
	arena.memory[15].value = 1;
	arena.memory[17].value = 58;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 & 1));
	ASSERT((int)process.carry, ==, (58 & 1) == 0);

	arena.memory[15].value = 52;
	arena.memory[17].value = 59;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[0], ==, (59 & 52));
	ASSERT((int)process.carry, ==, (59 & 52) == 0);

	// indirect + reg + reg
	process.current_instruction.args_type[0] = IND_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.pc = 0;
	process.current_instruction.args[0] = 2;
	process.current_instruction.args[1] = 3;
	process.current_instruction.args[2] = 0;
	process.registers[3] = 58;
	arena.memory[2].value = 1;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 & 1));
	ASSERT((int)process.carry, ==, (58 & 1) == 0);

	process.registers[3] = 59;
	arena.memory[2].value = 52;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[0], ==, (59 & 52));
	ASSERT((int)process.carry, ==, (59 & 52) == 0);

	// reg + direct + reg
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = DIR_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 1;
	process.current_instruction.args[1] = 58;
	process.current_instruction.args[2] = 0;
	process.registers[1] = 1;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 & 1));
	ASSERT((int)process.carry, ==, (58 & 1) == 0);

	process.current_instruction.args[0] = 3;
	process.registers[3] = 52;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 & 52));
	ASSERT((int)process.carry, ==, (58 & 52) == 0);

	// reg + indirect + reg
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = IND_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 1;
	process.current_instruction.args[1] = 58;
	process.current_instruction.args[2] = 0;
	process.pc = 0;
	process.registers[1] = 1;
	arena.memory[58].value = 58;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 & 1));
	ASSERT((int)process.carry, ==, (58 & 1) == 0);

	process.current_instruction.args[0] = 3;
	process.registers[3] = 52;
	arena.memory[58].value = 59;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[0], ==, (59 & 52));
	ASSERT((int)process.carry, ==, (59 & 52) == 0);

	// reg + reg + reg
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 3;
	process.current_instruction.args[1] = 2;
	process.current_instruction.args[2] = 1;
	process.registers[3] = -58;
	process.registers[2] = 1;
	process.registers[1] = 0;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[1], ==, (58 & 1));
	ASSERT((int)process.carry, ==, (58 & 1) == 0);

	process.registers[3] = 97;
	process.registers[2] = 13;
	process.registers[1] = 0;
	ins_and(&arena, &process);
	ASSERT((int)process.registers[1], ==, (97 & 13));
	ASSERT((int)process.carry, ==, (97 & 13) == 0);
}

void	test_ins_fork()
{
	t_arena		arena;
	t_process	process;

	init_arena(&arena);
	init_process(&process, NULL, 0);
	init_instruction(&process);
	process.current_instruction.args_type[0] = DIR_ARG;
	process.pc = 0;
	process.current_instruction.args[0] = 15;
	ins_fork(&arena, &process);
	ASSERT(process.next, !=, NULL);
	ASSERT((int)process.next->pc, ==, 15);
	free(process.next);

	process.current_instruction.args[0] = IDX_MOD * 3 + 30;
	ins_fork(&arena, &process);
	ASSERT(process.next, !=, NULL);
	ASSERT((int)process.next->pc, ==, 30);
	free(process.next);

	process.current_instruction.args[0] = -30;
	ins_fork(&arena, &process);
	ASSERT(process.next, !=, NULL);
	ASSERT((int)process.next->pc, ==, MEM_SIZE - 30);
	free(process.next);
}

void	test_ins_ld()
{
	t_arena		arena;
	t_process	process;

	init_arena(&arena);
	init_process(&process, NULL, 0);
	init_instruction(&process);

	// direct arg1
	process.current_instruction.args_type[0] = DIR_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args[0] = 15;
	process.current_instruction.args[1] = 5;
	ins_ld(&arena, &process);
	ASSERT((int)process.registers[5], ==, 15);
	ASSERT((int)process.carry, ==, 15 == 0);

	process.current_instruction.args[0] = -855;
	ins_ld(&arena, &process);
	ASSERT((int)process.registers[5], ==, -855);
	ASSERT((int)process.carry, ==, -855 == 0);

	process.current_instruction.args[0] = 0;
	ins_ld(&arena, &process);
	ASSERT((int)process.registers[5], ==, 0);
	ASSERT((int)process.carry, ==, 0 == 0);

	// indirect arg1
	process.current_instruction.args_type[0] = IND_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args[0] = MEM_SIZE;
	process.current_instruction.args[1] = 10;
	process.pc = 0;
	arena.memory[0].value = 7;
	ins_ld(&arena, &process);
	ASSERT((int)process.registers[10], ==, 7);
	ASSERT((int)process.carry, ==, 7 == 0);

	process.current_instruction.args[0] = -15;
	process.pc = 10;
	arena.memory[MEM_SIZE - 5].value = -13;
	ins_ld(&arena, &process);
	ASSERT((int)process.registers[10], ==, -13);
	ASSERT((int)process.carry, ==, -13 == 0);
}

void	test_ins_ldi()
{
	t_arena		arena;
	t_process	process;

	init_arena(&arena);
	init_process(&process, NULL, 0);
	init_instruction(&process);

	// direct + direct + reg
	process.current_instruction.args_type[0] = DIR_ARG;
	process.current_instruction.args_type[1] = DIR_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 58;
	process.current_instruction.args[1] = 120;
	process.current_instruction.args[2] = 11;
	process.pc = 10;
	arena.memory[10 + (58 + 120) % IDX_MOD].value = 73;
	ins_ldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, 73);

	process.current_instruction.args[0] = 0;
	process.current_instruction.args[1] = -5800;
	process.pc = 10;
	arena.memory[MEM_SIZE + 10 + -5800  % IDX_MOD].value = -10;
	ins_ldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, -10);

	// direct + reg + reg
	process.current_instruction.args_type[0] = DIR_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 15000;
	process.current_instruction.args[1] = 1;
	process.current_instruction.args[2] = 11;
	process.registers[1] = 89543;
	process.pc = 500;
	arena.memory[(500 + (15000 + 89543) % IDX_MOD) % MEM_SIZE].value = 42;
	ins_ldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, 42);

	process.current_instruction.args[0] = -150;
	process.current_instruction.args[1] = 1;
	process.current_instruction.args[2] = 11;
	process.registers[1] = 58;
	process.pc = 500;
	arena.memory[500 + (-150 + 58) % IDX_MOD].value = 47;
	ins_ldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, 47);

	// indirect + direct + reg
	process.current_instruction.args_type[0] = IND_ARG;
	process.current_instruction.args_type[1] = DIR_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 58;
	process.current_instruction.args[1] = 27;
	process.current_instruction.args[2] = 11;
	process.pc = 0;
	arena.memory[58].value = 3;
	arena.memory[(3 + 27) % IDX_MOD].value = 11;
	ins_ldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, 11);

	process.current_instruction.args[0] = -20;
	process.current_instruction.args[1] = 100;
	process.current_instruction.args[2] = 11;
	process.pc = 10;
	arena.memory[MEM_SIZE - 10].value = 55;
	arena.memory[10 + (55 + 100) % IDX_MOD].value = -58;
	ins_ldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, -58);

	// indirect + reg + reg
	process.current_instruction.args_type[0] = IND_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 789798;
	process.current_instruction.args[1] = 5;
	process.current_instruction.args[2] = 11;
	process.pc = 78;
	process.registers[5] = 123123;
	arena.memory[(78 + (789798 % IDX_MOD) % MEM_SIZE)].value = 47;
	arena.memory[(78 + (47 + 123123) % IDX_MOD) % MEM_SIZE].value = -9;
	ins_ldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, -9);

	process.current_instruction.args[0] = -48;
	process.current_instruction.args[1] = 5;
	process.current_instruction.args[2] = 11;
	process.pc = 78;
	process.registers[5] = -48;
	arena.memory[(78 + (-48 % IDX_MOD) % MEM_SIZE)].value = 5;
	arena.memory[(78 + (5 + -48) % IDX_MOD) % MEM_SIZE].value = 15;
	ins_ldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, 15);

	// reg + direct + reg
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = DIR_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 2;
	process.current_instruction.args[1] = 5858588;
	process.current_instruction.args[2] = 11;
	process.registers[2] = 77;
	process.pc = 50;
	arena.memory[(50 + (5858588 + 77) % IDX_MOD) % MEM_SIZE].value = 6;
	ins_ldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, 6);

	process.current_instruction.args[0] = 2;
	process.current_instruction.args[1] = -8881;
	process.current_instruction.args[2] = 11;
	process.registers[2] = 58;
	process.pc = 50;
	arena.memory[MEM_SIZE + 50 + (-8881 + 58) % IDX_MOD].value = 27;
	ins_ldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, 27);

	// reg + reg + reg
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 2;
	process.current_instruction.args[1] = 8;
	process.current_instruction.args[2] = 11;
	process.registers[2] = 77;
	process.registers[8] = 78;
	process.pc = 57;
	arena.memory[57 + (77 + 78) % IDX_MOD].value = 85;
	ins_ldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, 85);

	process.registers[2] = -58;
	process.registers[8] = -98;
	process.pc = 57;
	arena.memory[MEM_SIZE + 57 + (-58 + -98) % IDX_MOD].value = -27;
	ins_ldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, -27);
}

void	test_ins_lfork()
{
	t_arena		arena;
	t_process	process;

	init_arena(&arena);
	init_process(&process, NULL, 0);
	init_instruction(&process);
	process.current_instruction.args_type[0] = DIR_ARG;
	process.pc = 4500;
	process.current_instruction.args[0] = 8500;
	ins_lfork(&arena, &process);
	ASSERT(process.next, !=, NULL);
	ASSERT((int)process.next->pc, ==, (4500 + 8500) % MEM_SIZE);
	free(process.next);

	process.pc = 10;
	process.current_instruction.args[0] = -3000;
	ins_lfork(&arena, &process);
	ASSERT(process.next, !=, NULL);
	ASSERT((int)process.next->pc, ==, MEM_SIZE + 10 - 3000);
	free(process.next);
}

void	test_ins_live() // TODO
{
	t_arena		arena;
	t_process	process;
	int			i;

	init_arena(&arena);
	init_process(&process, NULL, 0);
	init_instruction(&process);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		arena.players[i].number = (i + 1) * 11;
		++i;
	}

	arena.nb_players = 4;
	arena.cycle = 31;
	process.current_instruction.args[0] = 33;
	ins_live(&arena, &process);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		ASSERT((int)arena.players[i].last_live, ==, i == 2 ? 31 : 0);
		++i;
	}
	ASSERT((int)process.last_live, ==, 31);
	ASSERT((int)arena.nb_lives, ==, 1);

	arena.cycle = 777;
	process.current_instruction.args[0] = 11;
	ins_live(&arena, &process);
	i = 0;
	while (i < MAX_PLAYERS)
	{
		ASSERT((int)arena.players[i].last_live, ==, i == 0 ? 777 : i == 2 ? 31 : 0);
		++i;
	}
	ASSERT((int)process.last_live, ==, 777);
	ASSERT((int)arena.nb_lives, ==, 2);
}

void	test_ins_lld()
{
	t_arena		arena;
	t_process	process;

	init_arena(&arena);
	init_process(&process, NULL, 0);
	init_instruction(&process);

	// direct arg1
	process.current_instruction.args_type[0] = DIR_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args[0] = 15;
	process.current_instruction.args[1] = 5;
	ins_lld(&arena, &process);
	ASSERT((int)process.registers[5], ==, 15);
	ASSERT((int)process.carry, ==, 15 == 0);

	process.current_instruction.args[0] = -855;
	ins_lld(&arena, &process);
	ASSERT((int)process.registers[5], ==, -855);
	ASSERT((int)process.carry, ==, -855 == 0);

	process.current_instruction.args[0] = 0;
	ins_lld(&arena, &process);
	ASSERT((int)process.registers[5], ==, 0);
	ASSERT((int)process.carry, ==, 0 == 0);

	// indirect arg1
	process.current_instruction.args_type[0] = IND_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args[0] = 3000;
	process.current_instruction.args[1] = 10;
	process.pc = 0;
	arena.memory[3000].value = 7;
	ins_lld(&arena, &process);
	ASSERT((int)process.registers[10], ==, 7);
	ASSERT((int)process.carry, ==, 7 == 0);

	process.current_instruction.args[0] = -15;
	process.pc = 10;
	arena.memory[MEM_SIZE - 5].value = -13;
	ins_lld(&arena, &process);
	ASSERT((int)process.registers[10], ==, -13);
	ASSERT((int)process.carry, ==, -13 == 0);
}

void	test_ins_lldi()
{
	t_arena		arena;
	t_process	process;

	init_arena(&arena);
	init_process(&process, NULL, 0);
	init_instruction(&process);

	// direct + direct + reg
	process.current_instruction.args_type[0] = DIR_ARG;
	process.current_instruction.args_type[1] = DIR_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 58;
	process.current_instruction.args[1] = 1200;
	process.current_instruction.args[2] = 11;
	process.pc = 10;
	arena.memory[10 + (58 + 1200)].value = 73;
	ins_lldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, 73);
	ASSERT((int)process.carry, ==, 73 == 0);

	process.current_instruction.args[0] = 0;
	process.current_instruction.args[1] = -7800;
	process.pc = 10;
	arena.memory[MEM_SIZE + MEM_SIZE + 10 + -7800].value = -10;
	ins_lldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, -10);
	ASSERT((int)process.carry, ==, -10 == 0);

	// direct + reg + reg
	process.current_instruction.args_type[0] = DIR_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 15000;
	process.current_instruction.args[1] = 1;
	process.current_instruction.args[2] = 11;
	process.registers[1] = 89543;
	process.pc = 500;
	arena.memory[(500 + (15000 + 89543)) % MEM_SIZE].value = 42;
	ins_lldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, 42);
	ASSERT((int)process.carry, ==, 42 == 0);

	process.current_instruction.args[0] = -2500;
	process.current_instruction.args[1] = 1;
	process.current_instruction.args[2] = 11;
	process.registers[1] = 58;
	process.pc = 500;
	arena.memory[MEM_SIZE + 500 + (-2500 + 58)].value = 0;
	ins_lldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, 0);
	ASSERT((int)process.carry, ==, 0 == 0);

	// indirect + direct + reg
	process.current_instruction.args_type[0] = IND_ARG;
	process.current_instruction.args_type[1] = DIR_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 58;
	process.current_instruction.args[1] = 27;
	process.current_instruction.args[2] = 11;
	process.pc = 0;
	arena.memory[58].value = 3;
	arena.memory[3 + 27].value = 11;
	ins_lldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, 11);
	ASSERT((int)process.carry, ==, 11 == 0);

	process.current_instruction.args[0] = -20;
	process.current_instruction.args[1] = 1585;
	process.current_instruction.args[2] = 11;
	process.pc = 10;
	arena.memory[MEM_SIZE - 10].value = 55;
	arena.memory[(10 + 55 + 1585) % MEM_SIZE].value = -58;
	ins_lldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, -58);
	ASSERT((int)process.carry, ==, -58 == 0);

	// indirect + reg + reg
	process.current_instruction.args_type[0] = IND_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 789798;
	process.current_instruction.args[1] = 5;
	process.current_instruction.args[2] = 11;
	process.pc = 78;
	process.registers[5] = 123123;
	arena.memory[(78 + 789798) % MEM_SIZE].value = 47;
	arena.memory[(78 + 47 + 123123) % MEM_SIZE].value = -9;
	ins_lldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, -9);
	ASSERT((int)process.carry, ==, -9 == 0);

	process.current_instruction.args[0] = -4800;
	process.current_instruction.args[1] = 5;
	process.current_instruction.args[2] = 11;
	process.pc = 878;
	process.registers[5] = -48;
	arena.memory[(MEM_SIZE + 878 + -4800)].value = 5;
	arena.memory[(MEM_SIZE + 878 + 5 + -4800)].value = 0;
	ins_lldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, 0);
	ASSERT((int)process.carry, ==, 0 == 0);

	// reg + direct + reg
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = DIR_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 2;
	process.current_instruction.args[1] = 5858588;
	process.current_instruction.args[2] = 11;
	process.registers[2] = 77;
	process.pc = 50;
	arena.memory[(50 + (5858588 + 77)) % MEM_SIZE].value = 6;
	ins_lldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, 6);
	ASSERT((int)process.carry, ==, 6 == 0);

	process.current_instruction.args[0] = 2;
	process.current_instruction.args[1] = -1881;
	process.current_instruction.args[2] = 11;
	process.registers[2] = 58;
	process.pc = 50;
	arena.memory[MEM_SIZE + 50 - 1881 + 58].value = 27;
	ins_lldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, 27);
	ASSERT((int)process.carry, ==, 27 == 0);

	// reg + reg + reg
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 2;
	process.current_instruction.args[1] = 8;
	process.current_instruction.args[2] = 11;
	process.registers[2] = 77;
	process.registers[8] = 78;
	process.pc = 57;
	arena.memory[57 + (77 + 78)].value = 0;
	ins_lldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, 0);
	ASSERT((int)process.carry, ==, 0 == 0);

	process.registers[2] = -580;
	process.registers[8] = -980;
	process.pc = 57;
	arena.memory[MEM_SIZE + 57 + (-580 + -980)].value = -27;
	ins_lldi(&arena, &process);
	ASSERT((int)process.registers[11], ==, -27);
	ASSERT((int)process.carry, ==, -27 == 0);
}

void	test_ins_or()
{
	t_arena		arena;
	t_process	process;

	init_arena(&arena);
	init_process(&process, NULL, 0);
	init_instruction(&process);

	// direct + direct + reg
	process.current_instruction.args_type[0] = DIR_ARG;
	process.current_instruction.args_type[1] = DIR_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 58;
	process.current_instruction.args[1] = 3;
	process.current_instruction.args[2] = 0;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 | 3));
	ASSERT((int)process.carry, ==, (58 | 3) == 0);

	process.current_instruction.args[0] = 69;
	process.current_instruction.args[1] = 11;
	process.current_instruction.args[2] = 0;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[0], ==, (69 | 11));
	ASSERT((int)process.carry, ==, (69 | 11) == 0);

	// direct + indirect + reg
	process.current_instruction.args_type[0] = DIR_ARG;
	process.current_instruction.args_type[1] = IND_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.pc = 0;
	process.current_instruction.args[0] = 58;
	process.current_instruction.args[1] = -10;
	process.current_instruction.args[2] = 0;
	arena.memory[MEM_SIZE - 10].value = 1;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 | 1));
	ASSERT((int)process.carry, ==, (58 | 1) == 0);

	arena.memory[MEM_SIZE - 10].value = 52;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 | 52));
	ASSERT((int)process.carry, ==, (58 | 52) == 0);

	// direct + reg + reg
	process.current_instruction.args_type[0] = DIR_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 58;
	process.current_instruction.args[1] = 1;
	process.current_instruction.args[2] = 0;
	process.registers[1] = 1;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 | 1));
	ASSERT((int)process.carry, ==, (58 | 1) == 0);

	process.current_instruction.args[1] = 3;
	process.registers[3] = 52;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 | 52));
	ASSERT((int)process.carry, ==, (58 | 52) == 0);

	// indirect + direct + reg
	process.current_instruction.args_type[0] = IND_ARG;
	process.current_instruction.args_type[1] = DIR_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.pc = 0;
	process.current_instruction.args[0] = 15;
	process.current_instruction.args[1] = 58;
	process.current_instruction.args[2] = 0;
	arena.memory[15].value = 1;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 | 1));
	ASSERT((int)process.carry, ==, (58 | 1) == 0);

	arena.memory[15].value = 52;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 | 52));
	ASSERT((int)process.carry, ==, (58 | 52) == 0);

	// indirect + indirect + reg
	process.current_instruction.args_type[0] = IND_ARG;
	process.current_instruction.args_type[1] = IND_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.pc = 0;
	process.current_instruction.args[0] = 15;
	process.current_instruction.args[1] = -170;
	process.current_instruction.args[2] = 0;
	arena.memory[15].value = 1;
	arena.memory[MEM_SIZE - 170].value = 58;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 | 1));
	ASSERT((int)process.carry, ==, (58 | 1) == 0);

	arena.memory[15].value = 52;
	arena.memory[MEM_SIZE - 170].value = 59;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[0], ==, (59 | 52));
	ASSERT((int)process.carry, ==, (59 | 52) == 0);

	// indirect + reg + reg
	process.current_instruction.args_type[0] = IND_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.pc = 0;
	process.current_instruction.args[0] = -20;
	process.current_instruction.args[1] = 3;
	process.current_instruction.args[2] = 0;
	process.registers[3] = 58;
	arena.memory[MEM_SIZE - 20].value = 1;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 | 1));
	ASSERT((int)process.carry, ==, (58 | 1) == 0);

	process.registers[3] = 59;
	arena.memory[MEM_SIZE - 20].value = 52;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[0], ==, (59 | 52));
	ASSERT((int)process.carry, ==, (59 | 52) == 0);

	// reg + direct + reg
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = DIR_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 1;
	process.current_instruction.args[1] = 58;
	process.current_instruction.args[2] = 0;
	process.registers[1] = 1;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 | 1));
	ASSERT((int)process.carry, ==, (58 | 1) == 0);

	process.current_instruction.args[0] = 3;
	process.registers[3] = 52;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 | 52));
	ASSERT((int)process.carry, ==, (58 | 52) == 0);

	// reg + indirect + reg
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = IND_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 1;
	process.current_instruction.args[1] = 58;
	process.current_instruction.args[2] = 0;
	process.pc = 0;
	process.registers[1] = 1;
	arena.memory[58].value = 58;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 | 1));
	ASSERT((int)process.carry, ==, (58 | 1) == 0);

	process.current_instruction.args[0] = 3;
	process.registers[3] = 52;
	arena.memory[58].value = 59;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[0], ==, (59 | 52));
	ASSERT((int)process.carry, ==, (59 | 52) == 0);

	// reg + reg + reg
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 3;
	process.current_instruction.args[1] = 2;
	process.current_instruction.args[2] = 1;
	process.registers[3] = -58;
	process.registers[2] = 1;
	process.registers[1] = 0;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[1], ==, (-58 | 1));
	ASSERT((int)process.carry, ==, (-58 | 1) == 0);

	process.registers[3] = 97;
	process.registers[2] = 13;
	process.registers[1] = 0;
	ins_or(&arena, &process);
	ASSERT((int)process.registers[1], ==, (97 | 13));
	ASSERT((int)process.carry, ==, (97 | 13) == 0);
}

void	test_ins_st()
{
	t_arena		arena;
	t_process	process;

	init_arena(&arena);
	init_process(&process, NULL, 0);
	init_instruction(&process);

	// register arg2
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args[0] = 3;
	process.current_instruction.args[1] = 5;
	process.registers[3] = -15;
	ins_st(&arena, &process);
	ASSERT((int)process.registers[5], ==, -15);

	process.current_instruction.args[0] = 5;
	process.current_instruction.args[1] = 8;
	ins_st(&arena, &process);
	ASSERT((int)process.registers[8], ==, -15);

	// indirect arg2
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = IND_ARG;
	process.current_instruction.args[0] = 3;
	process.current_instruction.args[1] = -3801;
	process.registers[3] = 98;
	process.pc = 0;
	ins_st(&arena, &process);
	ASSERT((int)arena.memory[MEM_SIZE + (-3801 % IDX_MOD)].value, ==, 98);

	process.current_instruction.args[0] = 3;
	process.current_instruction.args[1] = 520;
	process.registers[3] = -111;
	process.pc = 5;
	ins_st(&arena, &process);
	ASSERT((int)arena.memory[5 + (520 % IDX_MOD)].value, ==, -111);
}

void	test_ins_sti()
{
	t_arena		arena;
	t_process	process;

	init_arena(&arena);
	init_process(&process, NULL, 0);
	init_instruction(&process);

	// reg + reg + reg
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 0;
	process.current_instruction.args[1] = 1;
	process.current_instruction.args[2] = 2;
	process.registers[0] = -67;
	process.registers[1] = 780;
	process.registers[2] = 890;
	process.pc = 0;
	ins_sti(&arena, &process);
	ASSERT((int)arena.memory[(780 + 890) % IDX_MOD].value, ==, -67);

	process.registers[0] = 67;
	process.registers[1] = -78;
	process.registers[2] = -89;
	process.pc = 0;
	ins_sti(&arena, &process);
	ASSERT((int)arena.memory[MEM_SIZE + (-78 + -89) % IDX_MOD].value, ==, 67);

	// reg + reg + dir
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = DIR_ARG;
	process.current_instruction.args[0] = 0;
	process.current_instruction.args[1] = 1;
	process.current_instruction.args[2] = 777;
	process.registers[0] = -6;
	process.registers[1] = 781;
	process.pc = 0;
	ins_sti(&arena, &process);
	ASSERT((int)arena.memory[(781 + 777) % IDX_MOD].value, ==, -6);

	process.registers[0] = 7;
	process.registers[1] = -781;
	process.current_instruction.args[2] = -121;
	process.pc = 0;
	ins_sti(&arena, &process);
	ASSERT((int)arena.memory[MEM_SIZE + (-781 + -121) % IDX_MOD].value, ==, 7);

	// reg + dir + reg
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = DIR_ARG;
	process.current_instruction.args_type[2] = REG_ARG;

	process.current_instruction.args[0] = 0;
	process.current_instruction.args[1] = 888;
	process.current_instruction.args[2] = 1;
	process.registers[0] = -55;
	process.registers[1] = 782;
	process.pc = 10;
	ins_sti(&arena, &process);
	ASSERT((int)arena.memory[10 + (888 + 782) % IDX_MOD].value, ==, -55);

	process.registers[0] = 8;
	process.registers[1] = -788;
	process.current_instruction.args[1] = -123;
	process.pc = 0;
	ins_sti(&arena, &process);
	ASSERT((int)arena.memory[MEM_SIZE + (-123 + -788) % IDX_MOD].value, ==, 8);

	// reg + dir + dir
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = DIR_ARG;
	process.current_instruction.args_type[2] = DIR_ARG;
	process.current_instruction.args[0] = 3;
	process.current_instruction.args[1] = 89;
	process.current_instruction.args[2] = 755;
	process.registers[3] = -65;
	process.pc = 0;
	ins_sti(&arena, &process);
	ASSERT((int)arena.memory[(89 + 755) % IDX_MOD].value, ==, -65);

	process.registers[3] = 25;
	process.current_instruction.args[1] = -28;
	process.current_instruction.args[2] = -12;
	process.pc = 0;
	ins_sti(&arena, &process);
	ASSERT((int)arena.memory[MEM_SIZE + (-28 + -12) % IDX_MOD].value, ==, 25);

	// reg + ind + reg
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = IND_ARG;
	process.current_instruction.args_type[2] = REG_ARG;

	process.current_instruction.args[0] = 0;
	process.current_instruction.args[1] = 888;
	process.current_instruction.args[2] = 1;
	process.registers[0] = -45;
	process.registers[1] = 782;
	process.pc = 10;
	arena.memory[10 + 888 % IDX_MOD].value = 58;
	ins_sti(&arena, &process);
	ASSERT((int)arena.memory[10 + (58 + 782) % IDX_MOD].value, ==, -45);

	process.registers[0] = 80;
	process.registers[1] = -788;
	process.current_instruction.args[1] = -723;
	process.pc = 54;
	arena.memory[(MEM_SIZE + 54 + (-723 % IDX_MOD)) % MEM_SIZE].value = -65;
	ins_sti(&arena, &process);
	ASSERT((int)arena.memory[MEM_SIZE + 54 + ((-788 + -65) % IDX_MOD) % MEM_SIZE].value, ==, 80);

	// reg + ind + dir
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = IND_ARG;
	process.current_instruction.args_type[2] = DIR_ARG;

	process.current_instruction.args[0] = 0;
	process.current_instruction.args[1] = 812;
	process.current_instruction.args[2] = 788;
	process.registers[0] = -43;
	process.pc = 10;
	arena.memory[10 + 812 % IDX_MOD].value = 55;
	ins_sti(&arena, &process);
	ASSERT((int)arena.memory[10 + (55 + 788) % IDX_MOD].value, ==, -43);

	process.registers[0] = 81;
	process.current_instruction.args[1] = -721;
	process.current_instruction.args[2] = -787;
	process.pc = 54;
	arena.memory[(MEM_SIZE + 54 + (-721 % IDX_MOD)) % MEM_SIZE].value = -67;
	ins_sti(&arena, &process);
	ASSERT((int)arena.memory[MEM_SIZE + 54 + ((-787 + -67) % IDX_MOD) % MEM_SIZE].value, ==, 81);
}

void	test_ins_sub()
{
	t_arena		arena;
	t_process	process;

	init_arena(&arena);
	init_process(&process, NULL, 0);
	init_instruction(&process);

	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 3;
	process.current_instruction.args[1] = 4;
	process.current_instruction.args[2] = 5;

	// test avec tout à 0
	process.registers[3] = 0;
	process.registers[4] = 0;
	process.registers[5] = 0;
	ins_sub(&arena, &process);
	ASSERT((int)process.registers[3], ==, 0);
	ASSERT((int)process.registers[4], ==, 0);
	ASSERT((int)process.registers[5], ==, 0);
	ASSERT((int)process.carry, ==, 1);

	// test que reg3 = reg2-reg1 et que carry = 0 si reg3 != 0
	process.registers[3] = 5;
	process.registers[4] = 2;
	process.registers[5] = 10;
	ins_sub(&arena, &process);
	ASSERT((int)process.registers[3], ==, 5);
	ASSERT((int)process.registers[4], ==, 2);
	ASSERT((int)process.registers[5], ==, 3);
	ASSERT((int)process.carry, ==, 0);

	// test que reg3 = reg1+reg2 et que carry = 1 si reg3 == 0
	process.registers[3] = -15;
	process.registers[4] = -15;
	process.registers[5] = 10;
	ins_sub(&arena, &process);
	ASSERT((int)process.registers[3], ==, -15);
	ASSERT((int)process.registers[4], ==, -15);
	ASSERT((int)process.registers[5], ==, 0);
	ASSERT((int)process.carry, ==, 1);
}

void	test_ins_xor()
{
	t_arena		arena;
	t_process	process;

	init_arena(&arena);
	init_process(&process, NULL, 0);
	init_instruction(&process);

	// direct + direct + reg
	process.current_instruction.args_type[0] = DIR_ARG;
	process.current_instruction.args_type[1] = DIR_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 58;
	process.current_instruction.args[1] = 3;
	process.current_instruction.args[2] = 0;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 ^ 3));
	ASSERT((int)process.carry, ==, (58 ^ 3) == 0);

	process.current_instruction.args[0] = 69;
	process.current_instruction.args[1] = 11;
	process.current_instruction.args[2] = 0;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[0], ==, (69 ^ 11));
	ASSERT((int)process.carry, ==, (69 ^ 11) == 0);

	// direct + indirect + reg
	process.current_instruction.args_type[0] = DIR_ARG;
	process.current_instruction.args_type[1] = IND_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.pc = 0;
	process.current_instruction.args[0] = 58;
	process.current_instruction.args[1] = -10;
	process.current_instruction.args[2] = 0;
	arena.memory[MEM_SIZE - 10].value = 1;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 ^ 1));
	ASSERT((int)process.carry, ==, (58 ^ 1) == 0);

	arena.memory[MEM_SIZE - 10].value = 52;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 ^ 52));
	ASSERT((int)process.carry, ==, (58 ^ 52) == 0);

	// direct + reg + reg
	process.current_instruction.args_type[0] = DIR_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 58;
	process.current_instruction.args[1] = 1;
	process.current_instruction.args[2] = 0;
	process.registers[1] = 1;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 ^ 1));
	ASSERT((int)process.carry, ==, (58 ^ 1) == 0);

	process.current_instruction.args[1] = 3;
	process.registers[3] = 52;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 ^ 52));
	ASSERT((int)process.carry, ==, (58 ^ 52) == 0);

	// indirect + direct + reg
	process.current_instruction.args_type[0] = IND_ARG;
	process.current_instruction.args_type[1] = DIR_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.pc = 0;
	process.current_instruction.args[0] = 15;
	process.current_instruction.args[1] = 58;
	process.current_instruction.args[2] = 0;
	arena.memory[15].value = 1;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 ^ 1));
	ASSERT((int)process.carry, ==, (58 ^ 1) == 0);

	arena.memory[15].value = 52;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 ^ 52));
	ASSERT((int)process.carry, ==, (58 ^ 52) == 0);

	// indirect + indirect + reg
	process.current_instruction.args_type[0] = IND_ARG;
	process.current_instruction.args_type[1] = IND_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.pc = 0;
	process.current_instruction.args[0] = 15;
	process.current_instruction.args[1] = -170;
	process.current_instruction.args[2] = 0;
	arena.memory[15].value = 1;
	arena.memory[MEM_SIZE - 170].value = 58;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 ^ 1));
	ASSERT((int)process.carry, ==, (58 ^ 1) == 0);

	arena.memory[15].value = 52;
	arena.memory[MEM_SIZE - 170].value = 59;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[0], ==, (59 ^ 52));
	ASSERT((int)process.carry, ==, (59 ^ 52) == 0);

	// indirect + reg + reg
	process.current_instruction.args_type[0] = IND_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.pc = 0;
	process.current_instruction.args[0] = -20;
	process.current_instruction.args[1] = 3;
	process.current_instruction.args[2] = 0;
	process.registers[3] = 58;
	arena.memory[MEM_SIZE - 20].value = 1;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 ^ 1));
	ASSERT((int)process.carry, ==, (58 ^ 1) == 0);

	process.registers[3] = 59;
	arena.memory[MEM_SIZE - 20].value = 52;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[0], ==, (59 ^ 52));
	ASSERT((int)process.carry, ==, (59 ^ 52) == 0);

	// reg + direct + reg
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = DIR_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 1;
	process.current_instruction.args[1] = 58;
	process.current_instruction.args[2] = 0;
	process.registers[1] = 1;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 ^ 1));
	ASSERT((int)process.carry, ==, (58 ^ 1) == 0);

	process.current_instruction.args[0] = 3;
	process.registers[3] = 52;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 ^ 52));
	ASSERT((int)process.carry, ==, (58 ^ 52) == 0);

	// reg + indirect + reg
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = IND_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 1;
	process.current_instruction.args[1] = 58;
	process.current_instruction.args[2] = 0;
	process.pc = 0;
	process.registers[1] = 1;
	arena.memory[58].value = 58;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[0], ==, (58 ^ 1));
	ASSERT((int)process.carry, ==, (58 ^ 1) == 0);

	process.current_instruction.args[0] = 3;
	process.registers[3] = 52;
	arena.memory[58].value = 59;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[0], ==, (59 ^ 52));
	ASSERT((int)process.carry, ==, (59 ^ 52) == 0);

	// reg + reg + reg
	process.current_instruction.args_type[0] = REG_ARG;
	process.current_instruction.args_type[1] = REG_ARG;
	process.current_instruction.args_type[2] = REG_ARG;
	process.current_instruction.args[0] = 3;
	process.current_instruction.args[1] = 2;
	process.current_instruction.args[2] = 1;
	process.registers[3] = -58;
	process.registers[2] = 1;
	process.registers[1] = 0;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[1], ==, (-58 ^ 1));
	ASSERT((int)process.carry, ==, (-58 ^ 1) == 0);

	process.registers[3] = 97;
	process.registers[2] = 13;
	process.registers[1] = 0;
	ins_xor(&arena, &process);
	ASSERT((int)process.registers[1], ==, (97 ^ 13));
	ASSERT((int)process.carry, ==, (97 ^ 13) == 0);
}

void	test_ins_zjmp()
{
	t_arena		arena;
	t_process	process;

	init_arena(&arena);
	init_process(&process, NULL, 0);
	init_instruction(&process);

	process.current_instruction.args_type[0] = DIR_ARG;
	process.carry = 1;
	process.current_instruction.args[0] = 58;
	process.pc = 77;
	ins_zjmp(&arena, &process);
	ASSERT((int)process.pc, ==, 77 + 58);

	process.current_instruction.args[0] = -789;
	process.pc = 51;
	ins_zjmp(&arena, &process);
	ASSERT((int)process.pc, ==, (MEM_SIZE + 51 + -789 % IDX_MOD) % MEM_SIZE);

	process.current_instruction.args[0] = 78964;
	process.pc = 2510;
	ins_zjmp(&arena, &process);
	ASSERT((int)process.pc, ==, (2510 + 78964 % IDX_MOD) % MEM_SIZE);
}

void	test_instructions()
{
	RUN_TEST(test_ins_add);
	RUN_TEST(test_ins_and);
	RUN_TEST(test_ins_fork);
	RUN_TEST(test_ins_ld);
	RUN_TEST(test_ins_ldi);
	RUN_TEST(test_ins_lfork);
	RUN_TEST(test_ins_live);
	RUN_TEST(test_ins_lld);
	RUN_TEST(test_ins_lldi);
	RUN_TEST(test_ins_or);
	RUN_TEST(test_ins_st);
	RUN_TEST(test_ins_sti);
	RUN_TEST(test_ins_sub);
	RUN_TEST(test_ins_xor);
	RUN_TEST(test_ins_zjmp);
}
