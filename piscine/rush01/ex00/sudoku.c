/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sudoku.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/15 17:46:32 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/15 17:46:33 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "sudoku.h"

void	putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	print(char sudoku[9][9])
{
	int i;
	int j;

	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			write(1, &sudoku[i][j], 1);
			if (j != 8)
				putstr(" ");
			j++;
		}
		putstr("\n");
		i++;
	}
}

int		parse_lines(char **input, char sudoku[9][9])
{
	int hints;
	int i;
	int j;

	hints = 0;
	i = -1;
	while (++i < 9)
	{
		j = 0;
		while (input[i][j])
		{
			if (!(input[i][j] == '.' || input[i][j] <= '9' ||
				input[i][j] >= '0'))
				return (0);
			if (input[i][j] != '.')
				hints++;
			sudoku[i][j] = input[i][j];
			j++;
		}
		if (j != 9)
			return (0);
	}
	if (hints < 17)
		return (0);
	return (1);
}

int		solve(char sudoku[9][9], int i, int j)
{
	char num;

	if (i == 9)
		return (1);
	if (sudoku[i][j] != '.')
		return (j == 8 ? solve(sudoku, i + 1, 0) : solve(sudoku, i, j + 1));
	num = j % 2 == 0 ? '9' : '0';
	while ((j % 2 == 0 && num >= '1') || (j % 2 != 0 && num <= '9'))
	{
		sudoku[i][j] = num;
		if (is_valid(sudoku, i, j) && j == 8)
		{
			if (solve(sudoku, i + 1, 0))
				return (1);
		}
		else if (is_valid(sudoku, i, j))
			if (solve(sudoku, i, j + 1))
				return (1);
		sudoku[i][j] = '.';
		num = j % 2 == 0 ? num - 1 : num + 1;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	char sudoku[9][9];

	argc--;
	if (argc != 9)
	{
		putstr("Error\n");
		return (-1);
	}
	argv++;
	if (!parse_lines(argv, sudoku))
	{
		putstr("Error\n");
		return (-1);
	}
	if (!is_valid_grid(sudoku))
	{
		putstr("Error\n");
		return (-1);
	}
	solve(sudoku, 0, 0);
	print(sudoku);
}
