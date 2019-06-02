/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_any.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/16 15:20:30 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/16 15:20:32 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int	ft_any(char **tab, int (*f)(char*))
{
	if (!f || !tab)
		return (0);
	while (*tab)
		if (f(*tab++) == 1)
			return (1);
	return (0);
}
