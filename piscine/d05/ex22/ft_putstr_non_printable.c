/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putstr_non_printable.c                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/10 22:21:55 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/10 22:21:56 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

void	ft_putchar(char c);

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

char	*ft_strcpy(char *dest, char *src)
{
	char *dest_save;

	dest_save = dest;
	while (*src)
	{
		*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';
	return (dest_save);
}

void	ft_putnbr_hex(int nbr)
{
	int		base_size;
	char	base[16];

	ft_strcpy(base, "0123456789abcdef");
	base_size = 16;
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr *= -1;
	}
	if (nbr < base_size)
	{
		ft_putchar(base[nbr]);
	}
	else
	{
		ft_putnbr_hex(nbr / base_size);
		ft_putchar(base[nbr % base_size]);
	}
}

void	ft_putstr_non_printable(char *str)
{
	while (*str)
	{
		if (*str > 32 && *str < 126)
			ft_putchar(*str);
		else
		{
			ft_putchar('\\');
			if ((unsigned char)*str < 16)
				ft_putchar('0');
			ft_putnbr_hex((unsigned char)*str);
		}
		str++;
	}
}
