/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_print_comb2.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/04 19:15:01 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 10:31:24 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

void	ft_putchar(char c);

void	ft_print_if_unique(char *digits, int *should_print_comma)
{
	if (digits[0] * 10 + digits[1] < digits[2] * 10 + digits[3])
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
		ft_putchar(digits[0]);
		ft_putchar(digits[1]);
		ft_putchar(' ');
		ft_putchar(digits[2]);
		ft_putchar(digits[3]);
	}
}

void	ft_print_comb2(void)
{
	int		should_print_comma;
	char	digits[4];

	should_print_comma = 0;
	digits[0] = '0';
	while (digits[0] <= '9')
	{
		digits[1] = '0';
		while (digits[1] <= '9')
		{
			digits[2] = '0';
			while (digits[2] <= '9')
			{
				digits[3] = '0';
				while (digits[3] <= '9')
				{
					ft_print_if_unique(digits, &should_print_comma);
					digits[3]++;
				}
				digits[2]++;
			}
			digits[1]++;
		}
		digits[0]++;
	}
}
