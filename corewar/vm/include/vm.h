/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vveyrat- <vveyrat-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 22:11:10 by vveyrat-          #+#    #+#             */
/*   Updated: 2020/06/27 13:59:14 by vveyrat-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libasm.h"
# include "libft.h"
# include "libprintf.h"
# include "colors.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <ncurses.h>

# define MAX_ARGS		4
# define MAX_PLAYERS	4

# define MEM_SIZE		4096
# define CHAMP_MAX_SIZE	682
# define IDX_MOD		512
# define REG_SIZE		4

# define CYCLE_DELTA	50
# define CYCLE_TO_DIE	1536
# define MAX_CHECKS		10
# define NBR_LIVE		21

# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1

/*
** struct t_process - A process
** @registers:           The registers of the process
** @current_instruction: The current instruction being executed. NULL if no
**                       instruction is being executed.
** @process_number:      Number of the process (begin at 0)
** @instruction_end:     The cycle at which the current instruction finishes
** @last_live:           The last cycle when a live instruction was issued from
**                       this process
** @pc:                  The address of the Program Counter for this process
** @carry:               The carry flag
** @player:              Index of player concerned by the process
** @prev:                The prev process
** @next:                The next process
*/

typedef	struct			s_process
{
	unsigned int		registers[REGISTERS_COUNT];
	t_ins				current_instruction;
	int					process_number;
	size_t				instruction_end;
	size_t				last_live;
	size_t				pc;
	unsigned int		carry:1;
	int					player;
	struct s_process	*prev;
	struct s_process	*next;
}						t_process;

/*
** struct t_player - A player
** @filename:    The name of the champion file
** @header_size: Size of the header
** @name:        The name of the player program
** @comment:     The comment of the player program
** @number:      The number the player should issue with the live operation
** @is_alive:    Whether the player is alive or not
** @last_live:   The last cycle when player execture live instruction
*/

typedef	struct			s_player
{
	char				*filename;
	int					header_size;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[PROG_COMMENT_LENGTH + 1];
	int					number;
	int					is_alive;
	int					last_live;
}						t_player;

/*
** struct t_mem_cell - A memory cell
** @value:  The value of this memory cell
** @player: The player which last wrote in this cell
*/

typedef	struct			s_mem_cell
{
	char				value;
	t_player			*player;
}						t_mem_cell;

/*
** struct t_arena - The memory arena
** @nb_players:   The number of players playing in the arena
** @players:      The players playing in the arena
** @memory:       The memory of the arena
** @processes:    Chained list with all processes
** @last_process: Adress of last process in @processes
** @cycle:        The actual cycle
** @cycle_to_die: Decrement (-CYCLE_DELTA) each time nb_lives reach NB_LIVE
**                	or check_cycle_to_die reach CYCLE_TO_DIE
** @next_check:   Number of next check cycle
** @dump:         After dump cycles, quit the game and print memory
** @aff:          If == 0, print aff and live instructions
** @nb_lives:     Count of "live" instruction
** @check_cycles_to_die: Check counter, limit is MAX_CHECKS
** @visu:         Visu mode or not
** @window:       Window for ncurses
** @speed:        Speed of vm (only in visu mode)
** @nb_process:   Number of processes
*/

typedef	struct			s_arena
{
	unsigned char		nb_players;
	t_player			players[MAX_PLAYERS];
	t_mem_cell			memory[MEM_SIZE];
	t_process			*processes;
	t_process			*last_process;
	int					cycle;
	int					cycle_to_die;
	int					next_check;
	int					dump;
	int					aff;
	int					nb_lives;
	int					check_cycles_to_die;
	int					visu;
	WINDOW				*window;
	double				speed;
	int					nb_process;
}						t_arena;

/*
** Parsing funcitons :
*/

void					read_params(int ac, char **av, t_arena *arena);

/*
** Parsing player funcitons :
*/

void					check_player(t_arena *arena, char **av,
							int number, int index);
void					get_filename(t_arena *arena, char *filename,
							int player_id);
int						get_player_number(t_arena *arena, int number);
void					get_player_comment(t_arena *arena, int player_ind,
							t_prog_header *prog_header);
void					get_player_name(t_arena *arena, int player_ind,
							t_prog_header *prog_header);
int						read_pars_player(t_arena *arena, int fd,
							t_prog_header *prog_header);

/*
** Error and quit functions :
*/

void					error(int reason, t_arena *arena, char *info);
void					last_free(t_arena *arena);
void					free_and_exit(t_arena *arena);

/*
** Cycles and exec functions :
*/

void					cycle(t_arena *arena);
void					check_lives(t_arena *arena);
void					check_processes(t_arena *arena);
void					execute_all_processes(t_arena *arena);

/*
** Champion's instruction :
*/

int						ins_add(t_arena *arena, t_process *process);
int						ins_aff(t_arena *arena, t_process *process);
int						ins_and(t_arena *arena, t_process *process);
int						ins_fork(t_arena *arena, t_process *process);
int						ins_ld(t_arena *arena, t_process *process);
int						ins_ldi(t_arena *arena, t_process *process);
int						ins_lfork(t_arena *arena, t_process *process);
int						ins_live(t_arena *arena, t_process *process);
int						ins_lld(t_arena *arena, t_process *process);
int						ins_lldi(t_arena *arena, t_process *process);
int						ins_or(t_arena *arena, t_process *process);
int						ins_st(t_arena *arena, t_process *process);
int						ins_sti(t_arena *arena, t_process *process);
int						ins_sub(t_arena *arena, t_process *process);
int						ins_xor(t_arena *arena, t_process *process);
int						ins_zjmp(t_arena *arena, t_process *process);

/*
** Arena tools :
*/

void					write_in_memory(t_arena *arena, t_process *process,
							int value, uint32_t nb);
uint32_t				get_value_in_memory(t_arena *arena,
							t_process *process, int index);
int						init_arena(t_arena *arena);
void					fill_memory_cases(t_arena *arena);
void					init_player_process(t_arena *arena);

/*
** Players tools :
*/

void					init_players(t_arena *arena);
int						player_alive(t_arena *arena);
int						nb_process_player(t_arena *arena, int player_ind);

/*
** Process tools :
*/

void					del_process(t_process **process);
void					del_all_processes(t_process **process);
int						add_process(t_arena *arena, t_process **processes,
							t_process **new, int player_ind);
void					init_process(t_arena *arena, t_process *process,
							t_process **prev, int player_ind);
void					copy_registers(t_process *src, t_process *dest);
int						process_alive(t_arena *arena);

/*
** Instruction tools :
*/

void					init_instruction(t_process *browse);
void					get_opcode(t_arena *arena, t_process *browse);
void					get_instruction(t_arena *arena, t_process *browse);
void					get_ins_size(t_ins *ins, char *bin);

/*
** Printing functions :
*/

void					dump_memory(t_arena *arena);
void					print_winner(t_arena *arena);

/*
** Maths functions :
*/

int						ft_absolute(int nb);

/*
** Visualizer functions :
*/

void					init_screen(t_arena *arena);
void					draw_arena(t_arena *arena);
void					get_event(t_arena *arena);
void					draw_hud(t_arena *arena);

#endif
