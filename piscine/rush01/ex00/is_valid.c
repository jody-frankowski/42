/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   is_valid.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/15 21:42:01 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/15 21:42:04 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

void	init_array(int *array, int n)
{
	int i;

	i = 0;
	while (i < 9)
	{
		array[i] = n;
		i++;
	}
}

int		is_valid_square(char sudoku[9][9], int i, int j)
{
	int k;
	int l;
	int square[9];

	init_array(square, 0);
	k = i / 3 * 3;
	while (k < (i / 3 * 3) + 3)
	{
		l = (j / 3 * 3);
		while (l < (j / 3 * 3) + 3)
		{
			if (sudoku[k][l] != '.')
			{
				if (square[sudoku[k][l] - '0' - 1])
					return (0);
				else
					square[sudoku[k][l] - '0' - 1] = 1;
			}
			l++;
		}
		k++;
	}
	return (1);
}

int		is_valid_line_and_col(char sudoku[9][9], int i, int j)
{
	int k;
	int line[9];
	int col[9];

	init_array(line, 0);
	init_array(col, 0);
	k = -1;
	while (++k < 9)
	{
		if (sudoku[i][k] != '.')
		{
			if (line[sudoku[i][k] - '0' - 1])
				return (0);
			else
				line[sudoku[i][k] - '0' - 1] = 1;
		}
		if (sudoku[k][j] != '.')
		{
			if (col[sudoku[k][j] - '0' - 1])
				return (0);
			else
				col[sudoku[k][j] - '0' - 1] = 1;
		}
	}
	return (1);
}

int		is_valid_grid(char sudoku[9][9])
{
	int i;
	int j;

	i = 0;
	while (i < 9)
	{
		if (!is_valid_line_and_col(sudoku, i, i))
			return (0);
		i++;
	}
	i = 1;
	while (i < 8)
	{
		j = 1;
		while (j < 8)
		{
			if (!is_valid_square(sudoku, i, j))
				return (0);
			j += 3;
		}
		i += 3;
	}
	return (1);
}

int		is_valid(char sudoku[9][9], int i, int j)
{
	if (!is_valid_line_and_col(sudoku, i, j))
		return (0);
	if (!is_valid_square(sudoku, i, j))
		return (0);
	return (1);
}
