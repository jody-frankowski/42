/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   matches_to_remove.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jde-la-m <jde-la-m@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/02 18:29:57 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/02 21:19:33 by jde-la-m    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "alcu.h"
#include "get_next_line.h"
#include "libft.h"
#include <stdlib.h>

int	alcu_matches_to_rmv_ai(t_line *board, int num_lines, int line_matches)
{
	if (board[num_lines - 1].game_type == MISERE)
		return (ft_max(1, line_matches - (((line_matches - 1) / 4) * 4 + 1)));
	else
		return (ft_max(1, line_matches - ((line_matches / 4) * 4)));
}

int	alcu_matches_to_rmv_user(int line_matches)
{
	int		matches_to_rmv;
	char	*user_input;

	while (1)
	{
		ft_putstr(LYEL"How many matches do you want to remove? [1-");
		ft_putnbr(ft_min(line_matches, 3));
		ft_putstr("]: "RSET);
		if (get_next_line(0, &user_input) == 1)
		{
			matches_to_rmv = alcu_validate_user_input(line_matches, user_input);
			free(user_input);
			if (matches_to_rmv)
				return (matches_to_rmv);
		}
		else
			return (0);
		ft_putstr(ANSI_CURSOR_UP);
		ft_putstr(ANSI_CLR_LINE);
	}
}

int	alcu_matches_to_rmv(t_line *board, int num_lines, t_player turn_for)
{
	int line_matches;

	line_matches = board[num_lines - 1].matches;
	if (turn_for == AI)
		return (alcu_matches_to_rmv_ai(board, num_lines, line_matches));
	else
	{
		return (alcu_matches_to_rmv_user(line_matches));
	}
}
