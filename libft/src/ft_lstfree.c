/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** ft_lstfree - Remove and free a single element from a list based on its
**              content pointer
** @list: Pointer to the list to modify
** @content: Pointer to the element to remove
**
** ft_lstfree will remove and free and element from the linked list based on
** its content pointer. @content will also be freed as is.
*/

void	ft_lstfree(t_list **list, void *content)
{
	t_list *head;
	t_list *elem;

	if (!list || !*list)
		return ;
	head = *list;
	if ((*list)->content == content)
	{
		*list = (*list)->next;
		free(content);
		free(head);
		return ;
	}
	while (head)
	{
		if (head->next && head->next->content == content)
		{
			elem = head->next;
			head->next = head->next->next;
			free(content);
			free(elem);
			break ;
		}
		head = head->next;
	}
}
