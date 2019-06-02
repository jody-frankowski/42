/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   helpers.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/02 16:43:33 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/02 16:43:33 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "alcu.h"

int	alcu_max(t_line *board, int num_lines)
{
	int	i;
	int	max;

	i = 0;
	max = board[i].matches;
	while (i < num_lines)
	{
		if (board[i].matches > max)
			max = board[i].matches;
		i++;
	}
	return (max);
}
