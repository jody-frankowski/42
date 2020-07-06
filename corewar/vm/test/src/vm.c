/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by vveyrat-          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include "vm.h"

void	test_params()
{
	t_arena		*arena;
	char		**test = NULL;

	if (!(arena = malloc(sizeof(t_arena))))
		return ;
	if (init_arena(arena) == EXIT_FAILURE)
		return ;
	if (!(test = ft_strsplit("./vm -n 2 resources/turtle.cor -n 1 resources/helltrain.cor -dump 5000", ' ')))
		return ;
	read_params(9, test, arena);
	ASSERT_OBJ(strcmp, arena->players[1].filename, "resources/turtle.cor", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, arena->players[0].filename, "resources/helltrain.cor", == 0, ft_putstr_fd);
	ASSERT(arena->players[1].number, ==, 1);
	ASSERT(arena->players[0].number, ==, 0);
	ASSERT_OBJ(strcmp, (char*)arena->players[0].name, "helltrain", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, (char*)arena->players[0].comment, "choo-choo, motherf*****s !", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, (char*)arena->players[1].name, "turtle", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, (char*)arena->players[1].comment, "TURTLE FFS U LAMA", == 0, ft_putstr_fd);
	ASSERT(arena->dump, ==, 5001);
	
	last_free(arena);
	
	char		**test2 = NULL;
	if (!(arena = malloc(sizeof(t_arena))))
		return ;
	if (init_arena(arena) == EXIT_FAILURE)
		return ;
	if (!(test2 = ft_strsplit("./vm -n 2 resources/turtle.cor -n 3 resources/helltrain.cor -dump 5000 resources/bee_gees.cor resources/zork.cor", ' ')))
		return ;
	read_params(11, test2, arena);
	ASSERT_OBJ(strcmp, arena->players[0].filename, "resources/bee_gees.cor", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, arena->players[1].filename, "resources/turtle.cor", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, arena->players[2].filename, "resources/helltrain.cor", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, arena->players[3].filename, "resources/zork.cor", == 0, ft_putstr_fd);
	ASSERT(arena->players[0].number, ==, 0);
	ASSERT(arena->players[1].number, ==, 1);
	ASSERT(arena->players[2].number, ==, 2);
	ASSERT(arena->players[3].number, ==, 3);
	ASSERT_OBJ(strcmp, (char*)arena->players[0].name, "stayin' alive", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, (char*)arena->players[0].comment, "Ha, Ha, Ha, stayiiiiin' aliiiiiiiiiive", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, (char*)arena->players[1].name, "turtle", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, (char*)arena->players[1].comment, "TURTLE FFS U LAMA", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, (char*)arena->players[2].name, "helltrain", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, (char*)arena->players[2].comment, "choo-choo, motherf*****s !", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, (char*)arena->players[3].name, "zork", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, (char*)arena->players[3].comment, "I'M ALIIIIVE", == 0, ft_putstr_fd);
	ASSERT(arena->dump, ==, 5001);

	last_free(arena);
	
	char		**test3 = NULL;
	if (!(arena = malloc(sizeof(t_arena))))
		return ;
	if (init_arena(arena) == EXIT_FAILURE)
		return ;
	if (!(test3 = ft_strsplit("./vm -dump 6874 resources/turtle.cor resources/zork.cor", ' ')))
		return ;
	read_params(5, test3, arena);
	ASSERT_OBJ(strcmp, arena->players[0].filename, "resources/turtle.cor", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, arena->players[1].filename, "resources/zork.cor", == 0, ft_putstr_fd);
	ASSERT(arena->players[0].number, ==, 0);
	ASSERT(arena->players[1].number, ==, 1);
	ASSERT_OBJ(strcmp, (char*)arena->players[0].name, "turtle", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, (char*)arena->players[0].comment, "TURTLE FFS U LAMA", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, (char*)arena->players[1].name, "zork", == 0, ft_putstr_fd);
	ASSERT_OBJ(strcmp, (char*)arena->players[1].comment, "I'M ALIIIIVE", == 0, ft_putstr_fd);
	ASSERT(arena->dump, ==, 6875);

	exit(0);
}

void	test_inits()
{
	t_arena		*arena;
	t_process	*proc0 = NULL;
	t_process	*proc1 = NULL;
	t_process	*proc2 = NULL;
	t_process	*proc3 = NULL;
	// t_process	*temp = NULL;
	int			count = 0;

	if (!(arena = malloc(sizeof(t_arena))))
		return ;
	if (init_arena(arena) == EXIT_FAILURE)
		return ;
	ASSERT(arena->nb_players, ==, 0);
	ASSERT(arena->processes, ==, NULL);
	ASSERT(arena->last_process, ==, NULL);
	ASSERT(arena->cycle, ==, 0);
	ASSERT(arena->cycle_to_die, ==, CYCLE_TO_DIE);
	ASSERT(arena->next_check, ==, 0);
	ASSERT(arena->dump, ==, -1);
	ASSERT(arena->nb_lives, ==, 0);
	ASSERT(arena->check_cycles_to_die, ==, 0);
	ASSERT(arena->visu, ==, 0);
	ASSERT(arena->window, ==, NULL);
	ASSERT(arena->speed, ==, 500);
	while (count < MEM_SIZE)
	{
		ASSERT(arena->memory[count].value, ==, 0);
		ASSERT(arena->memory[count].player, ==, NULL);
		count++;
	}
	count = 0;
	while (count < MAX_PLAYERS)
	{
		ASSERT(arena->players[count].filename, ==, NULL);
		ASSERT(arena->players[count].header_size, ==, 0);
		ASSERT(arena->players[count].number, ==, -1);
		ASSERT(arena->players[count].is_alive, ==, 1);
		ASSERT(arena->players[count].last_live, ==, 0);
		count++;
	}
	count = 0;
	add_process(arena, &arena->processes, &proc0, 0);
	add_process(arena, &arena->processes, &proc1, 0);
	add_process(arena, &arena->processes, &proc2, 0);
	add_process(arena, &arena->processes, &proc3, 0);

	ASSERT(arena->processes->instruction_end, ==, (size_t)0);
	ASSERT(arena->processes->last_live, ==, (size_t)0);
	ASSERT(arena->processes->pc, ==, (size_t)0);
	ASSERT((int)arena->processes->carry, ==, 0);
	while (count < REGISTERS_COUNT)
	{
		ASSERT(arena->processes->registers[count], ==, (unsigned int)0);
		count++;
	}
	count = 0;
	ASSERT(arena->processes->prev, ==, NULL);
	ASSERT(arena->processes, ==, proc0);
	ASSERT(arena->processes->next, ==, proc1);

	arena->processes = arena->processes->next;
	ASSERT(arena->processes->instruction_end, ==, (size_t)0);
	ASSERT(arena->processes->last_live, ==, (size_t)0);
	ASSERT(arena->processes->pc, ==, (size_t)0);
	ASSERT((int)arena->processes->carry, ==, 0);
	while (count < REGISTERS_COUNT)
	{
		ASSERT(arena->processes->registers[count], ==, (unsigned int)0);
		count++;
	}
	count = 0;
	ASSERT(arena->processes->prev, ==, proc0);
	ASSERT(arena->processes, ==, proc1);
	ASSERT(arena->processes->next, ==, proc2);

	arena->processes = arena->processes->next;
	ASSERT(arena->processes->instruction_end, ==, (size_t)0);
	ASSERT(arena->processes->last_live, ==, (size_t)0);
	ASSERT(arena->processes->pc, ==, (size_t)0);
	ASSERT((int)arena->processes->carry, ==, 0);
	while (count < REGISTERS_COUNT)
	{
		ASSERT(arena->processes->registers[count], ==, (unsigned int)0);
		count++;
	}
	count = 0;
	ASSERT(arena->processes->prev, ==, proc1);
	ASSERT(arena->processes, ==, proc2);
	ASSERT(arena->processes->next, ==, proc3);

	arena->processes = arena->processes->next;
	ASSERT(arena->processes->instruction_end, ==, (size_t)0);
	ASSERT(arena->processes->last_live, ==, (size_t)0);
	ASSERT(arena->processes->pc, ==, (size_t)0);
	ASSERT((int)arena->processes->carry, ==, 0);
	while (count < REGISTERS_COUNT)
	{
		ASSERT(arena->processes->registers[count], ==, (unsigned int)0);
		count++;
	}
	count = 0;
	ASSERT(arena->processes->prev, ==, proc2);
	ASSERT(arena->processes, ==, proc3);
	ASSERT(arena->processes->next, ==, NULL);
}

void	test_process()
{
	t_arena		*arena;
	t_process	*proc0 = NULL;
	t_process	*proc1 = NULL;
	t_process	*proc2 = NULL;
	t_process	*proc3 = NULL;

	if (!(arena = malloc(sizeof(t_arena))))
		return ;
	init_arena(arena);
	//init_players(arena);
	add_process(arena, &arena->processes, &proc0, 0);
	add_process(arena, &arena->processes, &proc1, 0);
	add_process(arena, &arena->processes, &proc2, 0);
	add_process(arena, &arena->processes, &proc3, 0);

	/*ft_printf("\n\nprocesses : %15p | %15p | %15p\n", arena->processes->prev, arena->processes, arena->processes->next);
	ft_printf("proc0     : %15p | %15p | %15p\n", proc0->prev, proc0, proc0->next);
	ft_printf("proc1     : %15p | %15p | %15p\n", proc1->prev, proc1, proc1->next);
	ft_printf("proc2     : %15p | %15p | %15p\n", proc2->prev, proc2, proc2->next);
	ft_printf("proc3     : %15p | %15p | %15p\n", proc3->prev, proc3, proc3->next);*/

	del_all_processes(&arena->processes);/*
	ft_printf("proc0     : %15p | %15p | %15p\n", proc0->prev, proc0, proc0->next);
	ft_printf("proc1     : %15p | %15p | %15p\n", proc1->prev, proc1, proc1->next);
	ft_printf("proc2     : %15p | %15p | %15p\n", proc2->prev, proc2, proc2->next);
	ft_printf("proc3     : %15p | %15p | %15p\n", proc3->prev, proc3, proc3->next);*/
	ASSERT(arena->processes, ==, NULL);
	ASSERT(proc0, ==, NULL);
	ASSERT(proc1, ==, NULL);
	ASSERT(proc2, ==, NULL);
	ASSERT(proc3, ==, NULL);
}

void	test_vm()
{
	RUN_TEST(test_inits);
	RUN_TEST(test_params);
	//RUN_TEST(test_process);
}
