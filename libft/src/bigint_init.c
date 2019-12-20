/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bigint_init.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/05 23:23:55 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/12/05 23:23:55 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "bigint.h"

/*
** bigint_init() - Initialize @num and set it to 0
** @num: The bigint variable to set.
**
** Return: 1 on success, 0 on error.
*/

int		bigint_init(t_bigint num)
{
	num->sign = BIGINT_POS;
	if (!(num->val = malloc(1 * sizeof(*num->val))))
		return (0);
	num->val[0] = 0;
	num->size = 1;
	return (1);
}

/*
** bigint_free() - Free a bigint
** @num: The bigint to free.
*/

void	bigint_free(t_bigint num)
{
	free(num->val);
}
