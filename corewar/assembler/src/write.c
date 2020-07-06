/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "assembler.h"
#include "libasm.h"
#include "libft.h"

static uint64_t	prog_get_size(t_parse_data *parse_data)
{
	uint64_t	sum;
	size_t		i;
	t_ins		*ins;

	sum = 0;
	i = 0;
	while (i < parse_data->ins_directives->len)
	{
		ins = ft_array_get(parse_data->ins_directives, i);
		sum += ins->size;
		i++;
	}
	return (sum);
}

static bool		prog_write_header(int fd, t_parse_data *parse_data)
{
	t_txt_meta		*txt_meta;
	t_prog_header	prog_header;
	size_t			i;

	ft_bzero(&prog_header, sizeof(prog_header));
	prog_header.magic_number = ft_htobe32(PROG_MAGIC_NUMBER);
	prog_header.size = ft_htobe64(prog_get_size(parse_data));
	i = 0;
	while ((txt_meta =
			txt_directives_get_meta(NULL, parse_data->txt_directives, i)))
	{
		if (bstr_cmp(txt_meta->name, str_to_bstr(META_DIRECTIVE_NAME)) == 0)
			ft_memcpy(prog_header.name,
						txt_meta->value.str, txt_meta->value.len);
		if (bstr_cmp(txt_meta->name, str_to_bstr(META_DIRECTIVE_COMMENT)) == 0)
			ft_memcpy(prog_header.comment,
						txt_meta->value.str, txt_meta->value.len);
		i++;
	}
	if (write(fd, &prog_header, sizeof(prog_header)) == -1)
		return (false);
	return (true);
}

static bool		prog_write_instructions(int fd, t_parse_data *parse_data)
{
	size_t		i;
	t_ins		*ins;
	t_bin_ins	bin_ins;

	i = 0;
	while (i < parse_data->ins_directives->len)
	{
		ins = ft_array_get(parse_data->ins_directives, i);
		bin_ins = ins_to_bin_ins(ins);
		if (bin_ins.bin[0] != 0 && write(fd, bin_ins.bin, bin_ins.len) == -1)
			return (false);
		i++;
	}
	return (true);
}

/*
** prog_write_binary() - Write the binary file
** @parse_data: The t_parse_data to write
*/

void			prog_write_binary(t_parse_data *parse_data)
{
	int	fd;

	fd = open(parse_data->output_filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1)
	{
		perror("Error while opening .cor file");
		err_exit(parse_data);
	}
	if (!prog_write_header(fd, parse_data))
	{
		perror("Failed to write the program header");
		close(fd);
		err_exit(parse_data);
	}
	if (!prog_write_instructions(fd, parse_data))
	{
		perror("Failed to write the instructions");
		close(fd);
		err_exit(parse_data);
	}
	if (close(fd) == -1)
		err_exit(parse_data);
}
