/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   piece1.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/06 00:43:56 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/06 00:43:56 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "filler.h"
#include "libft.h"

int	read_piece(t_grid *piece)
{
	if (!read_grid_size(piece))
		return (0);
	if (!(piece->grid = malloc(sizeof(char) * piece->x * piece->y)))
		return (0);
	if (!read_grid(piece, 0))
	{
		free(piece->grid);
		return (0);
	}
	return (1);
}

int	place_piece(t_coord coord)
{
	char *num;

	num = ft_lltostr(coord.y, "0123456789");
	if (!num)
		return (0);
	ft_putstr(num);
	free(num);
	ft_putstr(" ");
	num = ft_lltostr(coord.x, "0123456789");
	if (!num)
		return (0);
	ft_putstr(num);
	free(num);
	ft_putstr("\n");
	return (1);
}
