/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_convert_base.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/12 13:00:21 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/12 13:00:23 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_wtf(char c, char *str)
{
	int index;

	index = 0;
	while (str[index])
	{
		if (c && str[index] == c)
			return (index);
		index++;
	}
	return (c ? -1 : index);
}

int		ft_base_is_valid(char *base)
{
	int i;
	int j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+' || base[i] < 32 || base[i] > 126)
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
	if (i <= 1)
		return (0);
	return (1);
}

int		ft_atoi_base(char *str, char *base)
{
	int result;
	int sign;

	if (!ft_base_is_valid(base))
		return (0);
	while (*str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f' || *str == ' ')
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while (*str)
	{
		if (ft_wtf(*str, base) >= 0)
			result = (result * ft_wtf(0, base)) + ft_wtf(*str, base);
		else
			return (0);
		str++;
	}
	return (result * sign);
}

void	ft_itoa(long nb, char *dst, char *base, int num_size)
{
	int base_size;

	if (nb < 0)
	{
		*dst = '-';
		dst++;
		nb *= -1;
	}
	base_size = ft_wtf(0, base);
	if (nb < base_size)
		*dst = base[nb];
	else
	{
		ft_itoa(nb / base_size, dst, base, num_size - 1);
		dst[num_size - 1] = base[nb % base_size];
	}
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char	*nb_converted;
	long	nb;
	long	nb_save;
	int		num_size;
	int		num_chars;

	if ((nb = ft_atoi_base(nbr, base_from)) && !ft_base_is_valid(base_to))
		return (0);
	nb_save = nb;
	if (nb == 0)
		num_size = 1;
	else
	{
		num_size = 0;
		while (nb_save != 0)
		{
			nb_save /= ft_wtf(0, base_to);
			num_size++;
		}
	}
	num_chars = sizeof(*nb_converted) * (num_size + 1 + (nb < 0 ? 1 : 0));
	nb_converted = (char *)malloc(num_chars);
	ft_itoa(nb, nb_converted, base_to, num_size);
	nb_converted[num_chars] = '\0';
	return (nb_converted);
}
