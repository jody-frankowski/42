/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_list_reverse_fun.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 20:56:20 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 20:56:24 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"

void	ft_list_reverse_fun(t_list *begin_list)
{
	t_list	*vars[4];
	void	*prev_data;
	void	*tmp_data;

	if (!begin_list || !begin_list->next)
		return ;
	vars[0] = begin_list->next;
	vars[2] = begin_list;
	prev_data = begin_list->data;
	vars[1] = begin_list->next;
	while (vars[1]->next)
	{
		vars[3] = vars[1]->next;
		tmp_data = vars[1]->data;
		vars[1]->next = vars[2];
		vars[1]->data = prev_data;
		vars[2] = vars[1];
		prev_data = tmp_data;
		vars[1] = vars[3];
	}
	begin_list->next = vars[1];
	begin_list->data = vars[1]->data;
	vars[1]->next = vars[2];
	vars[1]->data = prev_data;
	vars[0]->next = NULL;
}
