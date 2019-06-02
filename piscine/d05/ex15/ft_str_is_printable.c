/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_str_is_printable.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/09 16:49:07 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/09 16:49:10 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int	ft_str_is_printable(char *str)
{
	while (*str)
	{
		if (*str < 32 || *str > 126)
			return (0);
		str++;
	}
	return (1);
}
