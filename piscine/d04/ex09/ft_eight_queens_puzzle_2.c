/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_eight_queens_puzzle_2.c                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/07 22:53:39 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/07 22:53:41 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

void	ft_putchar(char c);

void	print_queens_pos(int board[8][8])
{
	int pos[8];
	int i;
	int j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			if (board[i][j])
				pos[j] = i;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < 8)
	{
		ft_putchar('0' + pos[i] + 1);
		i++;
	}
	ft_putchar('\n');
}

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

void	solve(int board[8][8], int row)
{
	int column;

	column = 0;
	while (column < 8)
	{
		if (is_valid(board, row, column))
		{
			if (row == 7)
			{
				board[row][column] = 1;
				print_queens_pos(board);
				board[row][column] = 0;
				return ;
			}
			board[row][column] = 1;
			solve(board, row + 1);
			board[row][column] = 0;
		}
		column++;
	}
	return ;
}

void	ft_eight_queens_puzzle_2(void)
{
	int board[8][8];
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
	solve(board, 0);
}
