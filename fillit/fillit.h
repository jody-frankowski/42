/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fillit.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/08 17:47:09 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/08 17:47:09 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdint.h>
# include "libft.h"

# define MAP_HEIGHT 21
# define TETRICHARSET ".#"
# define T_TETRI_WIDTH 4
# define TETRI_BLOCK_LEN 20

typedef struct				s_point
{
	uint8_t x;
	uint8_t y;
}							t_point;

/*
**	The left side of the tetri will be in the least significant bits The top
**	side of the tetri will be in the lower parts of the array
*/

typedef struct s_tetri		t_tetri;

struct						s_tetri
{
	uint16_t	tetri[T_TETRI_WIDTH];
	uint8_t		height;
	uint8_t		width;
	t_tetri		*previous_same;
	t_point		coord;
};

typedef struct s_tetri_17	t_tetri_17;

struct						s_tetri_17
{
	uint32_t		tetri[T_TETRI_WIDTH];
	uint8_t			height;
	uint8_t			width;
	t_tetri_17		*previous_same;
	t_point			coord;
};

uint16_t					g_map[16];
uint32_t					g_map_17[21];
t_tetri						g_tetris[26];
t_tetri_17					g_tetris_17[26];
uint8_t						g_num_tetris;
uint8_t						g_width;

void						init_17(void);
int							parse_input(int fd);
int							place_tetris(int i);
int							place_tetris_17(int i);
int							print_map(void);
int							solve(void);
int							tetri_is_valid(const char lines[4][5]);
int							is_same_tetri(t_tetri *a, t_tetri *b);
int							tetri_can_be_placed(
							uint8_t x,
							uint8_t y,
							t_tetri *tetri);
void						place_tetri(
							uint8_t x,
							uint8_t y,
							t_tetri *tetri);
void						remove_tetri(
							uint8_t x,
							uint8_t y,
							t_tetri *tetri);
int							tetri_can_be_placed_17(
							uint8_t x,
							uint8_t y,
							t_tetri_17 *tetri);
void						place_tetri_17(
							uint8_t x,
							uint8_t y,
							t_tetri_17 *tetri);
void						remove_tetri_17(
							uint8_t x,
							uint8_t y,
							t_tetri_17 *tetri);

#endif
