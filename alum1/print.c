/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jde-la-m <jde-la-m@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/02 21:29:10 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/02 23:30:25 by jde-la-m    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "alcu.h"
#include "libft.h"

void	alcu_print_error(void)
{
	ft_putendl_fd(RED "ERROR", 2);
}

void	alcu_print_header(t_line *board, int num_lines)
{
	ft_putstr(ANSI_CLR_SCREEN);
	ft_putendl("\n\t\t\t\033[42;1m    ALUM1    \033[0m\n");
	ft_putendl("\t    « Je peux perdre, mais je gagne toujours. »\n");
	ft_putendl("\t\tThis is a game based on matches.");
	ft_putendl("\t\tEach turn, you can remove between");
	ft_putendl("\t\t\e[1;93m1\e[0m and \e[1;93m3\e[0m matches\
	from the last line.\n");
	ft_putendl("\t\tWhoever removes the last one loses.");
	ft_putstr("\n\n");
	alcu_show_matches_to_remove(board, num_lines);
}

void	alcu_show_matches_to_remove(t_line *board, int num_lines)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (i < num_lines)
	{
		ft_putstr(BLYEL"[");
		ft_putnbr(board[i].matches);
		ft_putstr("]\t\t"RSET BOLD);
		if ((j = board[i].matches) < alcu_max(board, num_lines))
		{
			k = ((alcu_max(board, num_lines) * 2) - (j * 2)) / 2;
			while (k--)
				ft_putchar(' ');
		}
		j = board[i].matches;
		while (j--)
			ft_putstr(BOLD "| ");
		ft_putstr("\n" RSET);
		i++;
	}
	ft_putstr("\n");
}
