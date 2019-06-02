/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_count_if.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 10:53:25 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 10:55:16 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int	ft_count_if(char **tab, int (*f)(char *))
{
	int count;

	if (!tab || !f)
		return (0);
	count = 0;
	while (*tab)
		if (f(*tab++) == 1)
			count++;
	return (count);
}
