/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rush04.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/08 15:51:43 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/08 15:51:47 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

void	ft_putchar(char c);

void	print_line(char left, char middle, char right, int x)
{
	if (x > 0)
	{
		ft_putchar(left);
		x--;
	}
	while (x > 1)
	{
		ft_putchar(middle);
		x--;
	}
	if (x > 0)
		ft_putchar(right);
	ft_putchar('\n');
	return ;
}

void	rush(int x, int y)
{
	if (x <= 0 || y <= 0)
		return ;
	if (y > 0)
	{
		print_line('A', 'B', 'C', x);
		y--;
	}
	while (y > 1)
	{
		print_line('B', ' ', 'B', x);
		y--;
	}
	if (y > 0)
		print_line('C', 'B', 'A', x);
	return ;
}
