/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sorted_list_insert.c                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 22:53:04 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 22:53:04 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_sorted_list_insert(t_list **begin_list, void *data, int (*cmp)())
{
	t_list *head;
	t_list *tmp;

	if (!*begin_list && (*begin_list = ft_create_elem(data)))
		return ;
	if (cmp((*begin_list)->data, data) > 0)
	{
		tmp = (*begin_list);
		*begin_list = ft_create_elem(data);
		(*begin_list)->next = tmp;
		return ;
	}
	head = *begin_list;
	while (head->next)
	{
		if (cmp(head->next->data, data) > 0)
		{
			tmp = head->next;
			head->next = ft_create_elem(data);
			head->next->next = tmp;
			return ;
		}
		head = head->next;
	}
	head->next = ft_create_elem(data);
}
