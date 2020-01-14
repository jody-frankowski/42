/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gnl.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/08 17:42:27 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/08 17:42:27 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <stdio.h>

/*
** Kiss my ass moulinette!
*/

# define BUFF_SIZE 1024

typedef struct	s_file {
	int			fd;
	int			eof;
	size_t		bufsz;
	char		*buf;
}				t_file;

int				ft_gnl(const int fd, char **line);

#endif
