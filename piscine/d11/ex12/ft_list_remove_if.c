/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_list_remove_if.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 17:21:48 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 17:21:49 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list *prev;
	t_list *next;
	t_list *head;

	prev = NULL;
	head = *begin_list;
	while (head)
	{
		next = head->next;
		if (cmp(head->data, data_ref) == 0)
		{
			free(head);
			if (prev == NULL)
				(*begin_list) = next;
			else
				prev->next = next;
		}
		else
			prev = head;
		head = next;
	}
}
