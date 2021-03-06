/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   nmatch.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/15 11:37:20 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/15 11:37:22 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

int	nmatch(char *s1, char *s2)
{
	if (!*s1 && !*s2)
		return (1);
	if (*s2 == '*')
		return ((*s1 && nmatch(s1 + 1, s2)) + nmatch(s1, s2 + 1));
	if (*s1 != *s2)
		return (0);
	return (nmatch(s1 + 1, s2 + 1));
}
