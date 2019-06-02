/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sort_params.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 09:45:31 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 11:02:54 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

void	ft_putchar(char c);

void	ft_putstr(char *str)
{
	while (*str)
		ft_putchar(*str++);
}

int		ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	sort_params(int argc, char **argv)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (i < argc)
	{
		j = i;
		while (j < argc)
		{
			if (ft_strcmp(argv[i], argv[j]) > 0)
			{
				str = argv[i];
				argv[i] = argv[j];
				argv[j] = str;
			}
			j++;
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	argc--;
	argv++;
	sort_params(argc, argv);
	while (argc != 0)
	{
		ft_putstr(*argv++);
		ft_putchar('\n');
		argc--;
	}
	return (0);
}
