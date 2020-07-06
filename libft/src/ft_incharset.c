/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_incharset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
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
