/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmergesort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		set_new(t_list **new, t_list **head, t_list **node)
{
	*new = *node;
	*head = *new;
	*node = (*node)->next;
}

static void		set_head(t_list **head, t_list **node)
{
	(*head)->next = *node;
	*head = *node;
	*node = (*node)->next;
}

/*
** Splits a linked list in two halves, setting left and right accordingly
** @lst: The list to split
** @left: The resulting left half
** @right: The resulting right half
*/

static void		ft_lstsplit(t_list **lst, t_list **left, t_list **right)
{
	t_list *fast;
	t_list *slow;

	slow = *lst;
	fast = (*lst)->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			fast = fast->next;
			slow = slow->next;
		}
	}
	*left = *lst;
	*right = slow->next;
	slow->next = NULL;
}

static t_list	*ft_lstsortedmerge(t_list *left,
									t_list *right,
									int (*cmp)(t_list *, t_list *))
{
	t_list *new;
	t_list *head;

	if (cmp(left, right) < 0)
		set_new(&new, &head, &left);
	else
		set_new(&new, &head, &right);
	while (1)
	{
		if (right && left)
		{
			if (cmp(left, right) < 0)
				set_head(&head, &left);
			else
				set_head(&head, &right);
		}
		if (!right && (head->next = left))
			break ;
		if (!left && (head->next = right))
			break ;
	}
	return (new);
}

/*
** ft_lstmergesort - Merge sorts a linked list
** @lst: The list to sort
** @cmp: The comparison function to use
**
** Return: 1 on success, or 0 on error
*/

void			ft_lstmergesort(t_list **lst, int (*cmp)(t_list *, t_list *))
{
	t_list *left;
	t_list *right;

	if (!lst || !*lst || !(*lst)->next)
		return ;
	ft_lstsplit(lst, &left, &right);
	ft_lstmergesort(&left, cmp);
	ft_lstmergesort(&right, cmp);
	*lst = ft_lstsortedmerge(left, right, cmp);
}
