/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   spec.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 18:09:40 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/24 18:09:41 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns 0 if line isn't valid.
** Checks that the line is in the form \d+... with the last 3 characters
** being unique. The leading number must be strictly superior to 0.
*/

int		spec_valid(char *line)
{
	int		i;
	int		j;
	int		l;
	char	*num;

	j = 0;
	while (line[j] && line[j] != '\n')
		j++;
	if (j < 4)
		return (0);
	i = -1;
	while (++i < j - 3)
		if (line[i] < '0' || line[i] > '9')
			return (0);
	num = ft_strndup(line, j - 3);
	l = ft_atoi(num);
	free(num);
	if (l <= 0)
		return (0);
	j--;
	if (line[j] == line[j - 1] || line[j] == line[j - 2] ||
		line[j - 1] == line[j - 2])
		return (0);
	return (1);
}

t_spec	*get_spec(char *line)
{
	t_spec	*spec;
	char	*num;
	int		i;

	spec = (t_spec *)malloc((sizeof(*spec)));
	if (!spec)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	i--;
	spec->full = line[i--];
	spec->obstacle = line[i--];
	spec->empty = line[i];
	num = ft_strndup(line, i);
	spec->l = ft_atoi(num);
	free(num);
	return (spec);
}

int		in_spec(char c, t_spec *spec)
{
	return (c == spec->empty || c == spec->obstacle || c == '\n');
}
