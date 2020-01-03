/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   alcu.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/02 13:20:59 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/02 13:20:59 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ALCU_H
# define ALCU_H

# define ALCU_MIN_MATCHES 1
# define ALCU_MAX_MATCHES 10000

# define ALCU_TURN_MIN_MATCHES 1
# define ALCU_TURN_MAX_MATCHES 3

typedef enum	e_game_type {
	NORMAL,
	MISERE
}				t_game_type;

typedef enum	e_player {
	AI,
	USER,
	MAX = USER
}				t_player;

typedef struct	s_line {
	int			matches;
	int			should_start_first;
	t_game_type	game_type;
}				t_line;

int				alcu_buildboard(t_line **board, int fd);
int				alcu_get_matches(char *line);
int				alcu_max(t_line *board, int num_lines);
int				alcu_matches_to_rmv(t_line *board,
									int num_lines,
									t_player turn_for);
void			alcu_print_error(void);
void			alcu_print_header(t_line *board, int num_lines);
int				alcu_validate_user_input(int line_matches, char *user_input);
void			alcu_show_matches_to_remove(t_line *board, int num_lines);

#endif
