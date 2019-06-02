/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_list_merge.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 19:19:29 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 19:19:30 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_list.h"

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
