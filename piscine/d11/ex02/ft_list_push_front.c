/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_list_push_front.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 21:19:00 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 21:19:01 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_push_front(t_list **begin_list, void *data)
{
	t_list *elem;

	if (!begin_list)
		return ;
	elem = ft_create_elem(data);
	if (!elem)
		return ;
	if (!*begin_list)
		*begin_list = elem;
	else
	{
		elem->next = *begin_list;
		*begin_list = elem;
	}
}
