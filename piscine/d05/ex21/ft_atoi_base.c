/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi_base.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/10 21:28:40 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/10 21:28:42 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

int		ft_base_is_valid(char *base)
{
	int i;
	int j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	if (i < 2)
		return (0);
	return (1);
}

int		num_in_base(char c, char *base)
{
	int i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*strip_whitespace(char *str)
{
	while (*str == '\t' || *str == '\n' ||
			*str == '\v' || *str == '\f' ||
			*str == '\r' || *str == ' ')
	{
		str++;
	}
	return (str);
}

int		ft_atoi_base(char *str, char *base)
{
	int base_size;
	int result;
	int sign;

	base_size = ft_strlen(base);
	if (!ft_base_is_valid(base))
		return (0);
	str = strip_whitespace(str);
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (num_in_base(*str, base) >= 0)
	{
		result *= base_size;
		result += num_in_base(*str, base);
		str++;
	}
	return (result * sign);
}
