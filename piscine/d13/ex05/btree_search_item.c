/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   btree_search_item.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/20 14:46:48 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/20 14:46:49 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_btree.h"

void	*btree_search_item(t_btree *root,
						void *data_ref,
						int (*cmpf)(void *, void *))
{
	void *data;

	if (!root)
		return (NULL);
	data = btree_search_item(root->left, data_ref, cmpf);
	if (data)
		return (data);
	if (cmpf(root->item, data_ref) == 0)
		return (root->item);
	data = btree_search_item(root->right, data_ref, cmpf);
	if (data)
		return (data);
	return (NULL);
}
