/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H

# include "libasm.h"

/*
** struct s_parse_data - The current parsing data (singleton)
** @input_filename:  The name of the input file
** @output_filename: The name of the output file
** @file:            The whole source file content
** @txt_directives:  The textual metadata and instruction directives of the
**                   source file
** @ins_directives:  The instruction directives of the source file
*/

typedef struct	s_parse_data
{
	char			*input_filename;
	char			*output_filename;
	t_bstr			file;
	t_array			*parsing_errors;
	t_array			*txt_directives;
	t_array			*ins_directives;
}				t_parse_data;

void			err_exit(t_parse_data *parse_data);
void			free_parse_data(t_parse_data *parse_data);
size_t			parse_errors_count_type_error(t_array *errors);
void			prog_write_binary(t_parse_data *parse_data);
void			usage(char *program_name);

#endif
