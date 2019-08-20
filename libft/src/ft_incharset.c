/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_incharset.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/07 20:02:01 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 20:02:01 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/*
** Returns 1 if c is in charset, 0 if it isn't.
** charset should be a valid pointer.
** @c: The searched character
** @charset: The charset to search into
*/

int	ft_incharset(int c, const char *charset)
{
	while (*charset)
		if (c == *charset++)
			return (1);
	return (0);
}
