/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_TYPES_H
# define LIBASM_TYPES_H

/*
** enum t_error - An error type
**
** @ERR_OK: No error
** @ERR_USAGE: Usage error
** @ERR_CHAMP_NAME: Invalid champion name
** @ERR_CHAMP_NBR: Too many champions
** @ERR_CHAMP_COMMENT: Invalid champion comment
** @ERR_CHAMP_SIZE: Champion size is too large
** @ERR_PROG_HEADER_TOO_SMALL:
**   The program header is too small
** @ERR_PROG_HEADER_WRONG_MAGIC_NUMBER:
**   The program header has a wrong magic number value
*/

typedef enum					e_error
{
	ERR_OK,
	ERR_USAGE,
	ERR_INDEX,
	ERR_CHAMP_NAME,
	ERR_CHAMP_COMMENT,
	ERR_CHAMP_NBR,
	ERR_CHAMP_SIZE,
	ERR_PROG_HEADER_TOO_SMALL,
	ERR_PROG_HEADER_WRONG_MAGIC_NUMBER,
	ERR_PARAM,
	ERR_READING,
	ERR_MALLOC,
	ERR_INS
}								t_error;

/*
** ### SYNTAX ###
*/

/*
** WSP - Whitespace charset
*/

# define WSP " \t"

/*
** META_DIRECTIVE_NAME - The name metadata directive identifier
*/

# define META_DIRECTIVE_NAME "name"

/*
** META_DIRECTIVE_COMMENT - The comment metadata directive identifier
*/

# define META_DIRECTIVE_COMMENT "comment"

/*
** These chars are used for the parsing
*/

# define COMMENT_CHARS           "#;"
# define DIRECT_VALUE_CHAR       "%"
# define LABEL_CHAR              ":"
# define OPERANDS_SEPARATOR_CHAR ","
# define REGISTER_CHAR           "r"
# define META_DIRECTIVE_CHAR     "."
# define META_QUOTE_CHAR         "\""

/*
** These charsets are used for the parsing checks
*/

# define DECIMAL_VALUE_CHARSET "0123456789"
# define LABEL_CHARSET         "abcdefghijklmnopqrstuvwxyz_0123456789"
# define META_NAME_CHARSET     "abcdefghijklmnopqrstuvwxyz"

/*
** DIRECT_VALUE_MAX_LEN - The maximum length of a correct direct value string
** 11 = strlen("-2147483648")
*/

# define DIRECT_VALUE_MAX_LEN 11

/*
** ### TEXTUAL DIRECTIVES ###
*/

/*
** struct s_txt_meta - A textual metadata directive
** @name:  The metadata directive name
** @value: The metadata directive value
*/

typedef struct					s_txt_meta
{
	t_bstr		name;
	t_bstr		value;
}								t_txt_meta;

/*
** struct s_txt_ins - An instruction directive
** @label:      The optional label of this instruction
** @name:       The name of the instruction
** @args:       The args
** @args_count: The number of args
*/

typedef struct					s_txt_ins
{
	t_bstr		label;
	t_bstr		name;
	t_bstr		args[3];
	size_t		args_count;
}								t_txt_ins;

/*
** enum e_txt_directive_type - The type of a struct s_txt_directive tagged union
** @TXT_DIRECTIVE_TYPE_INS:  A textual instruction directive
** @TXT_DIRECTIVE_TYPE_META: A textual metadata directive
** @TXT_DIRECTIVE_TYPE_NONE: None of the above. Used to denote the absence of
**                           directive.
*/

enum							e_txt_directive_type
{
	TXT_DIRECTIVE_TYPE_INS,
	TXT_DIRECTIVE_TYPE_META,
	TXT_DIRECTIVE_TYPE_NONE,
};

/*
** union u_directive - A metadata or instruction textual directive
** @ins:  The textual instruction directive
** @meta: The textual metadata directive
*/

union							u_txt_directive
{
	t_txt_ins	ins;
	t_txt_meta	meta;
};

/*
** struct s_txt_directive - A metadata or instruction textual directive
** @type:      The type of @directive
** @directive: The textual directive
** @line:      The original line. Can be used to print parse errors.
** @line_num:  The line number. Can be used to print parse errors.
*/

typedef struct					s_txt_directive
{
	enum e_txt_directive_type	type;
	union u_txt_directive		directive;
	t_bstr						line;
	size_t						line_num;
}								t_txt_directive;

/*
** ### SYNTAX/SEMANTIC CHECKS ###
*/

/*
** struct s_check_data - A syntaxic/semantic check data container
** @line:           The line being checked
** @line_num:       The number of the line being checked
** @parsing_errors: The list of errors found so far
*/

typedef struct					s_check_data
{
	t_bstr		line;
	size_t		line_num;
	t_array		*parsing_errors;
}								t_check_data;

/*
** enum e_parse_error_type - The type of a parsing error
** @P_ERR_TYPE_ERROR:   An error
** @P_ERR_TYPE_WARNING: A warning
** @P_ERR_TYPE_COUNT:   The number of members in this enum
*/

typedef enum					e_parse_error_type
{
	P_ERR_TYPE_ERROR,
	P_ERR_TYPE_WARNING,
	P_ERR_TYPE_COUNT,
}								t_parse_error_type;

/*
** enum e_parse_error_msg - The message of a parsing error
** See g_parse_err_msg for their values.
*/

typedef enum					e_parse_error_msg
{
	P_ERR_MSG_FORBIDDEN_CHAR,
	P_ERR_MSG_INS_EMPTY_OPERAND,
	P_ERR_MSG_INS_FORBID_DIR_ARG,
	P_ERR_MSG_INS_FORBID_IND_ARG,
	P_ERR_MSG_INS_FORBID_REG_ARG,
	P_ERR_MSG_INS_GARBAGE,
	P_ERR_MSG_INS_INVALID_REGISTER,
	P_ERR_MSG_INS_LABEL_DUPLICATE,
	P_ERR_MSG_INS_LABEL_UNKNOWN,
	P_ERR_MSG_INS_LABEL_UNUSED,
	P_ERR_MSG_INS_MISS_COMMA,
	P_ERR_MSG_INS_MISS_DIRECT_VALUE,
	P_ERR_MSG_INS_MISS_LABEL_NAME,
	P_ERR_MSG_INS_MISS_LABEL_REF,
	P_ERR_MSG_INS_MISS_NAME,
	P_ERR_MSG_INS_MISS_REGISTER_NUMBER,
	P_ERR_MSG_INS_MISS_WSP_BETWEEN_LABEL_AND_INSTRUCTION,
	P_ERR_MSG_INS_UNKNOWN,
	P_ERR_MSG_INS_VALUE_LEN,
	P_ERR_MSG_INS_WRONG_OPERANDS_COUNT,
	P_ERR_MSG_INS_VAL_INT_MAX,
	P_ERR_MSG_INS_VAL_INT_MIN,
	P_ERR_MSG_INS_VAL_SHRT_MAX,
	P_ERR_MSG_INS_VAL_SHRT_MIN,
	P_ERR_MSG_META_DIRECTIVE_DUPLICATE,
	P_ERR_MSG_META_DIRECTIVE_UNKNOWN,
	P_ERR_MSG_META_GARBAGE,
	P_ERR_MSG_META_MISS_CLOSE_QUOTE,
	P_ERR_MSG_META_MISS_DIRECTIVE_COMMENT,
	P_ERR_MSG_META_MISS_DIRECTIVE_NAME,
	P_ERR_MSG_META_MISS_DOT,
	P_ERR_MSG_META_MISS_NAME,
	P_ERR_MSG_META_MISS_OPEN_QUOTE,
	P_ERR_MSG_META_MISS_VALUE,
	P_ERR_MSG_META_MISS_WSP_BETWEEN_NAME_AND_VALUE,
	P_ERR_MSG_META_TOO_LONG_COMMENT_DIRECTIVE,
	P_ERR_MSG_META_TOO_LONG_NAME_DIRECTIVE,
	P_ERR_MSG_COUNT,
}								t_parse_error_msg;

/*
** struct s_parse_error - A parsing error
** @type: The type of the error
** @msg:  The msg for this error
** @line: The original line
** @line_num: The line number of this error
** @column: The column where the error starts
** @len: The length of th error
*/

typedef struct					s_parse_error
{
	t_parse_error_type	type;
	t_parse_error_msg	msg;
	t_bstr				line;
	size_t				line_num;
	char				*column;
	size_t				len;
}								t_parse_error;

/*
** @g_parse_err_color: The colors of each error types
** @g_parse_err_msg:   The strings for each error messages
** @g_parse_err_type:  The types of errors
*/

extern char					*g_parse_err_color[P_ERR_TYPE_COUNT];
extern char					*g_parse_err_msg[P_ERR_MSG_COUNT];
extern char					*g_parse_err_type[P_ERR_TYPE_COUNT];

/*
** ### INSTRUCTIONS ###
*/

/*
** @INSTRUCTIONS_COUNT: The number of instructions
** @REGISTERS_COUNT:    The number of registers
*/

# define INSTRUCTIONS_COUNT 16
# define REGISTERS_COUNT    16

/*
** The bits used in t_ins_spec to specify the possible arguments types
*/

# define REG_ARG_BIT 1
# define DIR_ARG_BIT 2
# define IND_ARG_BIT 4

/*
** The sizes of the different arguments type
*/

# define REG_ARG_SIZE 1
# define DIR_ARG_SIZE 4
# define IND_ARG_SIZE 2

/*
** struct t_ins_spec - An instruction specification
** @mnemonic:   The mnemonic of the instruction
** @num_args:   The number of arguments of the instruction
** @args_types: The possible types of each argument, encoded as a OR of
**              *_ARG_BIT
** @opcode:     The opcode value for this instruction
** @num_cycles: The number of cycles the instruction takes
** @has_acb:    Whether the instruction has an argument coding byte or not
** @direct_arg_size: The size in bytes of a direct value for this instruction
**                   (2 or 4)
*/

typedef struct					s_ins_spec
{
	char			*mnemonic;
	size_t			num_args;
	char			args_types[3];
	size_t			opcode;
	size_t			num_cycles;
	unsigned int	has_acb:1;
	unsigned int	direct_arg_size:3;
}								t_ins_spec;

/*
** g_instructions - The global array of instructions specifications
*/

extern t_ins_spec			g_instructions[INSTRUCTIONS_COUNT];

/*
** enum t_arg_type - A kind of argument
** @NO_ARG:  An empty argument
** @REG_ARG: A register argument
** @DIR_ARG: A direct argument
** @IND_ARG: An indirect argument
*/

typedef enum					e_arg_type
{
	NO_ARG = 0,
	REG_ARG = 1,
	DIR_ARG = 2,
	IND_ARG = 3
}								t_arg_type;

/*
** struct t_ins - An instantiated instruction
** @instruction: The instruction it refers to. If this pointer is NULL, that
**               means that this is a label-only instruction.
** @args_type:   The type of each arguments
** @args:        The value of the arguments
** @size:        The size of the instruction (opcode + acb + args)
*/

typedef struct					s_ins
{
	t_ins_spec		*instruction;
	t_arg_type		args_type[3];
	uint32_t		args[3];
	uint8_t			size;
}								t_ins;

/*
** ### BINARY INSTRUCTIONS ###
*/

/*
** INS_MAX_SIZE - The maximum size of an instruction in binary
*/

# define INS_MAX_SIZE 11

/*
** struct t_bin_ins - The binary representation of an instruction
** @bin: The binary data of the instruction
** @len: The length of the binary data
**
** If bin_ins.bin[0] equals 0, it means that this bin_ins was the result of a
** label-only instruction (ins.instruction == NULL) conversion.
*/

typedef struct					s_bin_ins
{
	char		bin[INS_MAX_SIZE];
	uint8_t		len;
}								t_bin_ins;

/*
** ### PROGRAM ###
*/

/*
** @PROG_MAGIC_NUMBER: The magic number stored at the beginning of a program
**                     header
** @PROG_NAME_LENGTH: The length of the header field that stores the program
**                    name
** @PROG_COMMENT_LENGTH: The length of the header field that store the program
**                       comment
*/

# define PROG_MAGIC_NUMBER 0x00ea83f3
# define PROG_NAME_LENGTH 128
# define PROG_COMMENT_LENGTH 2048

/*
** struct t_prog_header - A program header
** @magic_number: The program magic number. Should be equal to
**                PROG_MAGIC_NUMBER.
** @name:         The program name
** @size:         The program size
** @comment:      The program comment
** @padding:      4 padding bytes that should equal 0
*/

struct							s_prog_header
{
	uint32_t	magic_number;
	uint8_t		name[PROG_NAME_LENGTH];
	uint64_t	size;
	uint8_t		comment[PROG_COMMENT_LENGTH];
	uint32_t	padding;
} __attribute__((packed));

typedef struct s_prog_header	t_prog_header;

/*
** struct t_program - A program
** @header:       The header of the program
** @instructions: The instructions of the program
*/

typedef struct					s_program
{
	t_prog_header	*header;
	t_ins			instructions[];
}								t_program;

/*
** ### MISC ###
*/

/*
** TERM_COLOR_END - ANSI Color SGR reset escape sequence
*/

# define TERM_COLOR_END "\e[0m"

#endif
