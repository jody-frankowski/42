/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm_functions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_FUNCTIONS_H
# define LIBASM_FUNCTIONS_H

# include "libasm_types.h"

t_array			*check_semantic_txt_directives(t_array *txt_directives);
t_array			*check_syntax_file(t_bstr file);
t_array			*file_to_txt_directives(t_bstr file);
char			*ins_to_str(t_ins ins);
t_txt_ins		*txt_directives_get_ins(t_check_data *data,
										t_array *txt_directives, size_t index);
t_txt_meta		*txt_directives_get_meta(t_check_data *data,
											t_array *txt_directives,
											size_t index);
t_ins_spec		*txt_ins_get_ins_spec(t_txt_ins txt_ins);
t_array			*txt_instructions_to_instructions(t_array *txt_directives);
t_ins			bin_to_ins(char bin[INS_MAX_SIZE]);
bool			bstr_array_add(t_array *bstr_array, t_bstr str);
bool			bstr_array_free(t_array *array1, t_array *array2);
bool			bstr_array_is_in(t_array *bstr_array, t_bstr str);
bool			check_semantic_txt_directives_ins_labels(t_check_data *data,
													t_array *txt_directives);
bool			check_semantic_txt_directives_meta(t_check_data *data,
													t_array *txt_directives);
void			check_semantic_txt_ins(t_check_data *data, t_txt_ins txt_ins);
void			check_syntax_charset(t_check_data *check_data, t_bstr str,
										char *charset);
void			check_syntax_ins(t_check_data *check_data, t_bstr str);
void			check_syntax_ins_arg_type(t_check_data *data, t_bstr str);
void			check_syntax_meta(t_check_data *check_data, t_bstr str);
void			check_txt_ins_arg(t_check_data *data, t_ins_spec *ins_spec,
									t_bstr arg, size_t i);
t_error			get_prog_header(char *buffer, size_t buffer_size,
									t_prog_header *prog_header);
bool			ins_args_ok(t_ins *ins);
int				ins_set_arg(t_ins *ins, size_t arg_num, char **bin);
bool			ins_equal(t_ins *a, t_ins *b);
void			ins_print(int fd, t_ins *ins);
void			ins_set_args_type(t_ins *ins, char **bin);
void			ins_set_size(t_ins *ins);
t_bin_ins		ins_to_bin_ins(t_ins *ins);
t_txt_directive	line_to_txt_directive(t_bstr line);
void			parse_error_print(int fd, t_parse_error *error, char *filename);
void			parse_errors_print(int fd, t_array *errors, char *filename);
void			perr(t_check_data *data, t_parse_error_msg msg, char *column,
						size_t len);
void			pwarn(t_check_data *data, t_parse_error_msg msg, char *column,
						size_t len);
t_ins			str_to_ins(char *str);
t_bstr			txt_ins_arg_get_label(t_bstr arg);
bool			txt_ins_arg_has_label_reference(t_bstr arg);
t_ins			txt_ins_to_ins(t_txt_ins txt_ins);
t_txt_ins		txt_to_txt_ins(t_bstr txt);
t_txt_meta		txt_to_txt_meta(t_bstr txt);

#endif
