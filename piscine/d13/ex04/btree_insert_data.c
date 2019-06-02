/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   btree_insert_data.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/20 13:51:21 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/20 13:51:22 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_btree.h"

void	btree_insert_data(t_btree **root,
						void *item,
						int (*cmpf)(void *, void *))
{
	if (!root || !cmpf)
		return ;
	if (!*root)
	{
		*root = btree_create_node(item);
		return ;
	}
	if (cmpf(item, (*root)->item) < 0)
		btree_insert_data(&((*root)->left), item, cmpf);
	else
		btree_insert_data(&((*root)->right), item, cmpf);
}
