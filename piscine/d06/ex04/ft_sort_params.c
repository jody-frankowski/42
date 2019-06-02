/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sort_params.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/11 10:08:38 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/11 10:08:39 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

void	ft_putchar(char c);

void	ft_putstr(char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
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

void	ft_sort_strings(char **strings, int n)
{
	char	*min;
	char	*temp;
	int		min_pos;
	int		i;
	int		j;

	i = 0;
	while (i < n)
	{
		min = strings[i];
		min_pos = i;
		j = i;
		while (j < n)
		{
			if (ft_strcmp(strings[j], min) < 0)
			{
				min_pos = j;
				min = strings[j];
			}
			j++;
		}
		temp = strings[i];
		strings[i++] = min;
		strings[min_pos] = temp;
	}
}

int		main(int argc, char **argv)
{
	int i;

	if (argc == 0)
		return (0);
	argv++;
	argc--;
	ft_sort_strings(argv, argc);
	i = 0;
	while (i < argc)
	{
		ft_putstr(argv[i]);
		ft_putchar('\n');
		i++;
	}
	return (0);
}
