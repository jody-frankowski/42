/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_list_push_params.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 23:35:57 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 23:35:58 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"

t_list	*ft_list_push_params(int ac, char **av)
{
	t_list *new;
	t_list *prev;

	prev = NULL;
	while (ac-- > 0)
	{
		new = ft_create_elem(*av);
		if (!new)
			return (NULL);
		new->next = prev;
		prev = new;
		av++;
	}
	return (prev);
}
