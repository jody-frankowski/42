/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_list_at.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/18 14:52:28 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 14:52:29 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"

t_list	*ft_list_at(t_list *begin_list, unsigned int nbr)
{
	if (nbr == 0 || !begin_list)
		return (NULL);
	return (nbr == 1 ? begin_list : ft_list_at(begin_list->next, nbr - 1));
}
