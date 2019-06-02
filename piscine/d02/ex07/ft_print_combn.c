/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_print_combn.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/05 09:40:27 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/05 10:32:54 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

void	ft_putchar(char c);

int		ft_pow(int num, int power)
{
	int result;
	int i;

	result = num;
	if (power == 0)
		return (1);
	i = 1;
	while (i < power)
	{
		result *= num;
		i++;
	}
	return (result);
}

int		ft_is_unique(char *digits, int n)
{
	int i;
	int j;
	int unique;

	i = 0;
	unique = 1;
	while (i < n - 1 && unique)
	{
		if (digits[i] >= digits[i + 1])
			unique = 0;
		j = i + 1;
		while (j < n && unique)
		{
			if (digits[i] == digits[j])
				unique = 0;
			j++;
		}
		i++;
	}
	return (unique);
}

void	ft_inc(char *digits, int n)
{
	if (digits[n - 1] == '9')
	{
		digits[n - 1] = '0';
		ft_inc(digits, n - 1);
	}
	else
	{
		digits[n - 1]++;
	}
}

void	ft_print_digits(char *digits, int n, int *should_print_comma)
{
	int i;

	i = 0;
	if (*should_print_comma)
	{
		ft_putchar(',');
		ft_putchar(' ');
	}
	else
	{
		*should_print_comma = 1;
	}
	while (i < n)
	{
		ft_putchar(digits[i]);
		i++;
	}
}

void	ft_print_combn(int n)
{
	char	digits[n];
	int		i;
	int		should_print_comma;

	i = 0;
	should_print_comma = 0;
	if (n <= 0 || n > 10)
	{
		return ;
	}
	while (i < n)
	{
		digits[i] = '0';
		i++;
	}
	i = 0;
	while (i < ft_pow(10, n) - 1)
	{
		ft_inc(digits, n);
		if (ft_is_unique(digits, n))
		{
			ft_print_digits(digits, n, &should_print_comma);
		}
		i++;
	}
}
