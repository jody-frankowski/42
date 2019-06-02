/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_list_foreach_if.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 16:35:05 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 16:35:06 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_list.h"

void	ft_list_foreach_if(
							t_list *begin_list,
							void (*f)(void *),
							void *data_ref,
							int (*cmp)()
)
{
	while (begin_list)
	{
		if (cmp(begin_list->data, data_ref) == 0)
			f(begin_list->data);
		begin_list = begin_list->next;
	}
}
