/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "assembler.h"
#include "libasm.h"
#include "libft.h"

/*
** set_output_filename() - Get the output filename based on the source filename
** @parse_data: The parse_data singleton that contains the input filename and in
**              which to store the output filename.
**
** If @filename ends with ".s", it will be replaced by ".cor", otherwise ".cor"
** is appended.
**
** On error this function calls exit().
*/

static void	set_output_filename(t_parse_data *parse_data)
{
	char	*input_filename;
	size_t	input_filename_len;

	input_filename = parse_data->input_filename;
	input_filename_len = ft_strlen(input_filename);
	parse_data->output_filename = (char*)malloc(
		sizeof(*parse_data->output_filename) * (input_filename_len + 4 + 1));
	if (!parse_data->output_filename)
		err_exit(parse_data);
	ft_strcpy(parse_data->output_filename, input_filename);
	if (input_filename_len >= 2 &&
		ft_strequ(input_filename + input_filename_len - 2, ".s"))
		ft_strcpy(parse_data->output_filename + input_filename_len - 2, ".cor");
	else
		ft_strcat(parse_data->output_filename, ".cor");
}

/*
** free_parse_data() - Free the parse data singleton
** @parse_data: The pointer to the parse data to free
*/

void		free_parse_data(t_parse_data *parse_data)
{
	if (parse_data->output_filename)
		free(parse_data->output_filename);
	if (parse_data->file.str)
		free(parse_data->file.str);
	if (parse_data->txt_directives)
		ft_array_free(parse_data->txt_directives);
	if (parse_data->ins_directives)
		ft_array_free(parse_data->ins_directives);
	if (parse_data->parsing_errors)
		ft_array_free(parse_data->parsing_errors);
}

/*
** init_parse_data() - Initialize the parse data singleton
** @parse_data: The pointer to the structure to initialize
** @filename:   The name of the source file to convert
**
** On error this function calls exit().
*/

static void	init_parse_data(t_parse_data *parse_data, char *filename)
{
	int	fd;
	int	size;

	ft_bzero(parse_data, sizeof(*parse_data));
	parse_data->input_filename = filename;
	set_output_filename(parse_data);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		err_exit(parse_data);
	parse_data->file.str = NULL;
	size = ft_read_all(fd, &(parse_data->file.str));
	if (close(fd) == -1)
		err_exit(parse_data);
	if (size == -1)
		err_exit(parse_data);
	parse_data->file.len = size;
}

/*
** assemble() - Assemble a source file to its binary representation
** @filename: The file to assemble
**
** Return: On success true. On error false.
*/

static bool	assemble(char *filename)
{
	t_parse_data	parse_data;

	init_parse_data(&parse_data, filename);
	if (!(parse_data.parsing_errors = check_syntax_file(parse_data.file)))
		err_exit(&parse_data);
	parse_errors_print(2, parse_data.parsing_errors, parse_data.input_filename);
	if (parse_errors_count_type_error(parse_data.parsing_errors) > 0)
		err_exit(&parse_data);
	ft_array_free(parse_data.parsing_errors);
	parse_data.txt_directives = file_to_txt_directives(parse_data.file);
	if (!parse_data.txt_directives)
		err_exit(&parse_data);
	if (!(parse_data.parsing_errors =
			check_semantic_txt_directives(parse_data.txt_directives)))
		err_exit(&parse_data);
	parse_errors_print(2, parse_data.parsing_errors, parse_data.input_filename);
	if (parse_errors_count_type_error(parse_data.parsing_errors) > 0)
		err_exit(&parse_data);
	if (!(parse_data.ins_directives =
		txt_instructions_to_instructions(parse_data.txt_directives)))
		err_exit(&parse_data);
	prog_write_binary(&parse_data);
	free_parse_data(&parse_data);
	return (true);
}

int			main(int argc, char *argv[])
{
	if (argc == 2)
	{
		if (assemble(argv[1]))
			return (0);
		else
			return (1);
	}
	else
	{
		usage(argv[0]);
		return (1);
	}
}
