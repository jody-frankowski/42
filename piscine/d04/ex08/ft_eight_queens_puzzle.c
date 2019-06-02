/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_eight_queens_puzzle.c                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/06 15:51:25 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/06 15:51:28 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int		is_valid(int board[8][8], int row, int column)
{
	int i;
	int j;

	i = 0;
	while (i < 8)
	{
		if (board[row][i] || board[i][column])
			return (0);
		i++;
	}
	i = row;
	j = 0;
	while (i >= 0)
	{
		if (column - j >= 0)
			if (board[i][column - j])
				return (0);
		if (column + j < 8)
			if (board[i][column + j])
				return (0);
		i--;
		j++;
	}
	return (1);
}

void	solve(int board[8][8], int *solutions, int row)
{
	int column;

	column = 0;
	while (column < 8)
	{
		if (is_valid(board, row, column))
		{
			if (row == 7)
			{
				(*solutions)++;
				return ;
			}
			board[row][column] = 1;
			solve(board, solutions, row + 1);
			board[row][column] = 0;
		}
		column++;
	}
	return ;
}

int		ft_eight_queens_puzzle(void)
{
	int board[8][8];
	int solutions;
	int i;
	int j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			board[i][j] = 0;
			j++;
		}
		i++;
	}
	solutions = 0;
	solve(board, &solutions, 0);
	return (solutions);
}
