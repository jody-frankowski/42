/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_sorted_list_merge.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 23:20:19 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 23:20:19 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*head;
	t_list	*search;
	t_list	*min;
	void	*temp_data;

	head = *begin_list;
	while (head)
	{
		min = head;
		search = head->next;
		while (search)
		{
			if (cmp(min->data, search->data) > 0)
				min = search;
			search = search->next;
		}
		temp_data = head->data;
		head->data = min->data;
		min->data = temp_data;
		head = head->next;
	}
}

void	ft_list_merge(t_list **begin_list1, t_list *begin_list2)
{
	t_list *head;

	if (!*begin_list1)
	{
		*begin_list1 = begin_list2;
		return ;
	}
	head = *begin_list1;
	while (head->next)
	{
		head = head->next;
	}
	head->next = begin_list2;
}

void	ft_sorted_list_merge(t_list **begin_list1,
							t_list *begin_list2,
							int (*cmp)())
{
	ft_list_merge(begin_list1, begin_list2);
	ft_list_sort(begin_list1, cmp);
}
