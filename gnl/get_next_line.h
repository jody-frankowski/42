/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/20 14:45:39 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/20 14:45:39 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

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

int				get_next_line(const int fd, char **line);

#endif
