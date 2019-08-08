/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstissorted.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/15 15:17:06 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/15 15:17:06 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstissorted(t_list *lst, int (*cmp)(t_list *, t_list *))
{
	while (lst)
	{
		if (lst->next && cmp(lst, lst->next) > 0)
			return (0);
		lst = lst->next;
	}
	return (1);
}
