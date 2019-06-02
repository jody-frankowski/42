/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_list_sort.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 19:48:51 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 19:48:52 by jfrankow    ###    #+. /#+    ###.fr     */
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
