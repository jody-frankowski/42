/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strcapitalize.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/09 15:42:57 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/09 15:42:58 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

void	ft_char_lowcase(char *c)
{
	if (*c >= 'A' && *c <= 'Z')
		*c += 32;
}

void	ft_char_upcase(char *c)
{
	if (*c >= 'a' && *c <= 'z')
		*c -= 32;
}

int		ft_char_is_numeric(char c)
{
	if (c < '0' || c > '9')
		return (0);
	else
		return (1);
}

int		ft_char_is_alpha(char c)
{
	if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z'))
		return (0);
	else
		return (1);
}

char	*ft_strcapitalize(char *str)
{
	char	*save;
	int		should_capitalize_next_alpha;

	save = str;
	should_capitalize_next_alpha = 1;
	while (*str)
	{
		if (!ft_char_is_alpha(*str))
			should_capitalize_next_alpha = 1;
		if (ft_char_is_numeric(*str))
			should_capitalize_next_alpha = 0;
		if (should_capitalize_next_alpha && ft_char_is_alpha(*str))
		{
			ft_char_upcase(str);
			should_capitalize_next_alpha = 0;
		}
		else
		{
			ft_char_lowcase(str);
		}
		str++;
	}
	return (save);
}
