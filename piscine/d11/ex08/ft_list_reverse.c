/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_list_reverse.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 15:37:01 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 15:37:02 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"

void	ft_list_reverse(t_list **begin_list)
{
	t_list *prev;
	t_list *tmp_next;

	if (!*begin_list)
		return ;
	prev = NULL;
	while (*begin_list)
	{
		tmp_next = (*begin_list)->next;
		(*begin_list)->next = prev;
		prev = (*begin_list);
		(*begin_list) = tmp_next;
	}
	*begin_list = prev;
}
