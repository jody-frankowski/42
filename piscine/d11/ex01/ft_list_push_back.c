/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_list_push_back.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 20:50:39 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 20:50:40 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_push_back(t_list **begin_list, void *data)
{
	t_list *elem;
	t_list *ptr;

	if (!begin_list)
		return ;
	elem = ft_create_elem(data);
	if (!elem)
		return ;
	if (!*begin_list)
		*begin_list = elem;
	else
	{
		ptr = *begin_list;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = elem;
	}
}
