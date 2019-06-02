/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/09 11:25:48 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/09 11:25:49 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

char	*ft_strstr(char *str, char *to_find)
{
	int i;
	int same;

	if (!*to_find)
		return (str);
	while (*str)
	{
		same = 1;
		i = 0;
		while (to_find[i])
		{
			if (to_find[i] != str[i])
				same = 0;
			if (!str[i])
				break ;
			i++;
		}
		if (same)
			return (str);
		str++;
	}
	return (0);
}
