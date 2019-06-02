/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_print_comb.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/04 12:04:00 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 10:29:42 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

void	ft_putchar(char c);

void	ft_print_if_unique(char a, char b, char c, int *should_print_comma)
{
	if (a != b && b != c && a != c && a < b && b < c)
	{
		if (*should_print_comma)
		{
			ft_putchar(',');
			ft_putchar(' ');
		}
		else
		{
			*should_print_comma = 1;
		}
		ft_putchar(a);
		ft_putchar(b);
		ft_putchar(c);
	}
}

void	ft_print_comb(void)
{
	char	a;
	char	b;
	char	c;
	int		should_print_comma;

	a = '0';
	b = '0';
	c = '0';
	should_print_comma = 0;
	while (a <= '9')
	{
		b = '0';
		while (b <= '9')
		{
			c = '0';
			while (c <= '9')
			{
				ft_print_if_unique(a, b, c, &should_print_comma);
				c++;
			}
			b++;
		}
		a++;
	}
}
