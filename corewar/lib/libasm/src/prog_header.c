/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include "libft.h"

static t_error	prog_header_set_magic_number(
	char **buffer,
	t_prog_header *prog_header
)
{
	ft_memcpy(
		&prog_header->magic_number,
		*buffer,
		sizeof(prog_header->magic_number));
	prog_header->magic_number = ft_betoh32(prog_header->magic_number);
	if (prog_header->magic_number != PROG_MAGIC_NUMBER)
		return (ERR_PROG_HEADER_WRONG_MAGIC_NUMBER);
	*buffer += sizeof(prog_header->magic_number);
	return (ERR_OK);
}

static void		prog_header_set_name(
	char **buffer,
	t_prog_header *prog_header
)
{
	size_t i;

	i = 0;
	while (i < PROG_NAME_LENGTH)
	{
		prog_header->name[i] = (*buffer)[i];
		i++;
	}
	*buffer += i;
}

static void		prog_header_set_size(
	char **buffer,
	t_prog_header *prog_header
)
{
	ft_memcpy(&prog_header->size, *buffer, sizeof(prog_header->size));
	prog_header->size = ft_betoh64(prog_header->size);
	*buffer += sizeof(prog_header->size);
}

static void		prog_header_set_comment(
	char **buffer,
	t_prog_header *prog_header
)
{
	size_t i;

	i = 0;
	while (i < PROG_COMMENT_LENGTH)
	{
		prog_header->comment[i] = (*buffer)[i];
		i++;
	}
	*buffer += i;
}

/*
** get_prog_header() - Read a t_prog_header from a buffer
** @buffer:      The buffer to read from
** @buffer_size: The size of the buffer
** @prog_header: A pointer to a t_prog_header to read into
**
** Return: ERR_OK on success, otherwise a representative t_error.
*/

t_error			get_prog_header(
	char *buffer,
	size_t buffer_size,
	t_prog_header *prog_header
)
{
	t_error error;

	if (buffer_size < sizeof(t_prog_header))
		return (ERR_PROG_HEADER_TOO_SMALL);
	error = prog_header_set_magic_number(&buffer, prog_header);
	if (error != ERR_OK)
		return (error);
	prog_header_set_name(&buffer, prog_header);
	prog_header_set_size(&buffer, prog_header);
	prog_header_set_comment(&buffer, prog_header);
	return (ERR_OK);
}
