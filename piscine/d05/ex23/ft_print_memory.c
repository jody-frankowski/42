/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_print_memory.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/10 22:54:18 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/10 22:54:19 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

void	ft_putchar(char c);

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

void	ft_putnbr_hex(unsigned char nbr, int padding)
{
	unsigned char		base_size;
	char				base[16];

	ft_strcpy(base, "0123456789abcdef");
	base_size = 16;
	if (nbr < base_size)
	{
		if (padding > 1)
			ft_putnbr_hex(0, --padding);
		ft_putchar(base[nbr]);
	}
	else
	{
		ft_putnbr_hex(nbr / base_size, --padding);
		ft_putchar(base[nbr % base_size]);
	}
}

void	ft_print_chars(void *addr)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (*((char*)addr) < 32 || *((char*)addr) > 126)
			ft_putchar('.');
		else
			ft_putchar(*((char*)addr));
		i++;
		addr++;
	}
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	void			*save;
	unsigned char	address;
	int				i;

	save = addr;
	address = 0;
	while (size > 0)
	{
		ft_putnbr_hex(address, 8);
		ft_putchar(':');
		ft_putchar(' ');
		i = 0;
		while (i < 16)
		{
			ft_putnbr_hex(*((unsigned char*)addr++), 2);
			if (i % 2 == 1)
				ft_putchar(' ');
			address++;
			i++;
		}
		ft_print_chars(addr - 16);
		ft_putchar('\n');
		size--;
	}
	return (save);
}
