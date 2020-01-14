/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   filler.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/06 00:43:56 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/06 00:43:56 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define PIECE_SYM '*'
# define MAP_EMPTY_SYM '.'

typedef struct	s_coord
{
	int x;
	int y;
}				t_coord;

typedef struct	s_grid
{
	int		x;
	int		y;
	char	*grid;
}				t_grid;

typedef struct	s_player
{
	char symbol;
}				t_player;

typedef struct	s_strategy
{
	t_coord target;
}				t_strategy;

union			u_float
{
	float	x;
	int		i;
};

float			distance(t_coord a, t_coord b);

int				init_map(t_grid *map);
int				read_map(t_grid *map);

char			get_grid_cell(t_grid grid, int x, int y);
int				read_grid(t_grid *grid, int is_map);
int				read_grid_size(t_grid *grid);

t_coord			get_player_coords(t_grid map, t_player player);
int				read_players_infos(t_player *player, t_player *enemy);

void			init_strat(t_strategy *strat, t_grid map, t_player enemy);

int				read_piece(t_grid *piece);
int				place_piece(t_coord coord);
t_coord			choose_piece_placement(
						t_grid piece,
						t_grid map,
						t_strategy strat,
						t_player player);

#endif
