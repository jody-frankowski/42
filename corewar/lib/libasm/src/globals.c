/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

t_ins_spec	g_instructions[INSTRUCTIONS_COUNT] =
{
	{"live", 1, {DIR_ARG_BIT}, 1, 10, 0, 4},
	{"ld", 2, {DIR_ARG_BIT | IND_ARG_BIT, REG_ARG_BIT}, 2, 5, 1, 4},
	{"st", 2, {REG_ARG_BIT, IND_ARG_BIT | REG_ARG_BIT}, 3, 5, 1, 0},
	{"add", 3, {REG_ARG_BIT, REG_ARG_BIT, REG_ARG_BIT}, 4, 10, 1, 0},
	{"sub", 3, {REG_ARG_BIT, REG_ARG_BIT, REG_ARG_BIT}, 5, 10, 1, 0},
	{"and", 3, {REG_ARG_BIT | DIR_ARG_BIT | IND_ARG_BIT,
			REG_ARG_BIT | IND_ARG_BIT | DIR_ARG_BIT, REG_ARG_BIT}, 6, 6, 1, 4},
	{"or", 3, {REG_ARG_BIT | IND_ARG_BIT | DIR_ARG_BIT,
			REG_ARG_BIT | IND_ARG_BIT | DIR_ARG_BIT, REG_ARG_BIT}, 7, 6, 1, 4},
	{"xor", 3, {REG_ARG_BIT | IND_ARG_BIT | DIR_ARG_BIT,
			REG_ARG_BIT | IND_ARG_BIT | DIR_ARG_BIT, REG_ARG_BIT}, 8, 6, 1, 4},
	{"zjmp", 1, {DIR_ARG_BIT}, 9, 20, 0, 2},
	{"ldi", 3, {REG_ARG_BIT | DIR_ARG_BIT | IND_ARG_BIT,
			DIR_ARG_BIT | REG_ARG_BIT, REG_ARG_BIT}, 10, 25, 1, 2},
	{"sti", 3, {REG_ARG_BIT, REG_ARG_BIT | DIR_ARG_BIT | IND_ARG_BIT,
			DIR_ARG_BIT | REG_ARG_BIT}, 11, 25, 1, 2},
	{"fork", 1, {DIR_ARG_BIT}, 12, 800, 0, 2},
	{"lld", 2, {DIR_ARG_BIT | IND_ARG_BIT, REG_ARG_BIT}, 13, 10, 1, 4},
	{"lldi", 3, {REG_ARG_BIT | DIR_ARG_BIT | IND_ARG_BIT,
			DIR_ARG_BIT | REG_ARG_BIT, REG_ARG_BIT}, 14, 50, 1, 2},
	{"lfork", 1, {DIR_ARG_BIT}, 15, 1000, 0, 2},
	{"aff", 1, {REG_ARG_BIT}, 16, 2, 1, 0},
};

char *g_parse_err_msg[P_ERR_MSG_COUNT] = {
	"Forbidden character",
	"Empty operand",
	"Direct value operand is forbidden there",
	"Indirect value operand is forbidden there",
	"Register operand is forbidden there",
	"Garbage after instruction operands",
	"Invalid register",
	"Duplicate label",
	"Unknown label",
	"Unused label",
	"Missing comma between operands",
	"Missing direct value after direct value symbol '"DIRECT_VALUE_CHAR"'",
	"Missing label name before label symbol '"LABEL_CHAR"'",
	"Missing label reference after label symbol '"LABEL_CHAR"'",
	"Missing instruction name",
	"Missing register number after register symbol '"REGISTER_CHAR"'",
	"Missing whitespace between label and instruction",
	"Unknown instruction",
	"Values can't be longer than 11 characters",
	"Wrong number of operands for this instruction",
	"Value can't be higher than 2147483647",
	"Value can't be lower than -2147483648",
	"Value can't be higher than 32767",
	"Value can't be lower than -32768",
	"Duplicate metadata directive (last one will be used)",
	"Unknown metadata directive",
	"Garbage after metadata directive value",
	"Missing closing quote after metadata directive value",
	"Missing metadata directive '."META_DIRECTIVE_COMMENT"'",
	"Missing metadata directive '."META_DIRECTIVE_NAME"'",
	"Missing '.' before directive name",
	"Missing metadata directive name after '"META_DIRECTIVE_CHAR"'",
	"Missing opening quote before metadata directive value",
	"Missing metadata directive value",
	"Missing whitespace between metadata directive name and its value",
	"."META_DIRECTIVE_COMMENT" directive value is too long (> 2048)"
	" (will be truncated)",
	"."META_DIRECTIVE_NAME" directive value is too long (> 128)"
	" (will be truncated)",
};

char *g_parse_err_type[P_ERR_TYPE_COUNT] = {
	"error",
	"warning",
};

char *g_parse_err_color[P_ERR_TYPE_COUNT] = {
	"\e[31m",
	"\e[35m",
};
