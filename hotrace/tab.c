/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 18:19:58 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/06 18:19:58 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree(t_tab *alst)
{
	t_tab *prev;

	while (alst)
	{
		prev = alst;
		alst = alst->next;
		free(prev);
	}
}

void	free_tab(void)
{
	int i;

	i = 0;
	while (i < TAB_LEN)
	{
		ft_lstfree(g_tab[i].next);
		i++;
	}
}
