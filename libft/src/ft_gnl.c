/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "gnl.h"
#include "libft.h"

/*
** get_or_add() - Add a new fd to the list of files
** @files: Pointer to the list of files to get from or add to
** @fd:    File descriptor to get or add
**
** Return: Pointer to the existing file
*/

static t_file	*get_or_add(t_list **files, const int fd)
{
	t_list *elem;
	t_list *head;

	head = *files;
	while (head && ((t_file *)head->content)->fd != fd)
		head = head->next;
	if (!head)
	{
		if (!(elem = ft_lstnew(&(t_file){fd, 0, 0, NULL}, sizeof(t_file))))
			return (NULL);
		ft_lstpush(files, elem);
		return (elem->content);
	}
	else
		return (head->content);
}

/*
** gnl_free() - Free helper #norminette
** @files: A list of t_file to free
** @f:     A file to free
*/

static int		gnl_free(t_list **files, t_file *f)
{
	free(f->buf);
	ft_lstfree(files, f);
	return (1);
}

/*
** gnl_set_line() - Second part of gnl #Norm
** @files: A saved list of files being read
** @f:     The current file being read
** @line:  A pointer to the line that will be returned
** @nlptr: A pointer to the next \n char in @f->buf
*/

static int		gnl_set_line(
							t_list **files,
							t_file *f,
							char **line,
							char *nlptr
)
{
	if (f->eof && f->bufsz == 0 && gnl_free(files, f))
		return (0);
	if (f->eof)
	{
		if (!(*line = ft_bstrdup(f->buf, f->bufsz)))
			return (-1);
		f->bufsz = 0;
	}
	if (nlptr)
	{
		if (!(*line = ft_bstrdup(f->buf, nlptr - f->buf)))
			return (-1);
		f->bufsz -= nlptr - f->buf + 1;
		if (!ft_bstrtrunc((void **)&(f->buf), nlptr - f->buf + 1, f->bufsz))
		{
			f->bufsz += nlptr - f->buf + 1;
			return (-1);
		}
	}
	if (f->bufsz == 0)
		gnl_free(files, f);
	return (1);
}

/*
** gnl() - Read a line
** @fd:   File descriptor to read from
** @line: Pointer to the string that will be set by the function
**
** gnl will read a line (or what remains) from the file descriptor @fd
** into the argument line.
** The function uses a static variable to keep track of the different file
** descriptors and what was already read.
** It is considered to be undefined behavior if the caller does any read/seek
** on @fd between calls.
** The function doesn't read on its stack so that if a malloc fails, what was
** read is never lost.
** In case of error the function won't free its data and will try to keep
** its internal state in proper order. We consider that since
** this is an important library function, it should aim at not losing any
** data.
**
** When eof is hit, it's possible that bufsz is smaller than the malloc buffer.
** At this point it would represent the number of bytes read.
**
** Return: 1 if something was read. 0 if nothing was read. -1 on error.
*/

int				ft_gnl(const int fd, char **line)
{
	static t_list	*files;
	t_file			*f;
	char			*nlptr;
	int				ret;

	if (!line || fd < 0)
		return (-1);
	if (!(f = get_or_add(&files, fd)))
		return (-1);
	ret = f->bufsz;
	while (!(nlptr = ft_memchr(f->buf + f->bufsz - ret, '\n', ret)) && !f->eof)
	{
		if (!(f->buf = ft_reallocf(f->buf, f->bufsz, f->bufsz + BUFF_SIZE)) ||
			((ret = read(fd, f->buf + f->bufsz, BUFF_SIZE)) == -1))
		{
			if (f->bufsz == 0)
				gnl_free(&files, f);
			return (-1);
		}
		f->bufsz += ret;
		f->eof = ret == 0 ? 1 : 0;
	}
	return (gnl_set_line(&files, f, line, nlptr));
}
