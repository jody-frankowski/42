/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   btree_level_count.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/20 14:58:35 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/20 14:58:36 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_btree.h"

int	btree_level_count(t_btree *root)
{
	int left;
	int right;

	if (!root)
		return (0);
	left = btree_level_count(root->left);
	right = btree_level_count(root->right);
	return (1 + (left > right ? left : right));
}
