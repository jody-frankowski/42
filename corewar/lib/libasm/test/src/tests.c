/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libasm.h"
#include "libunit.h"

static bool txt_directive_equal(t_txt_directive a, t_txt_directive b)
{
	if (a.type != b.type)
		return (false);
	if (a.type == TXT_DIRECTIVE_TYPE_META)
	{
		if (bstr_cmp(a.directive.meta.name, b.directive.meta.name) != 0 ||
			bstr_cmp(a.directive.meta.value, b.directive.meta.value) != 0)
			return (false);
	}
	if (a.type == TXT_DIRECTIVE_TYPE_INS)
	{
		if (bstr_cmp(a.directive.ins.label, b.directive.ins.label) != 0 ||
			bstr_cmp(a.directive.ins.name, b.directive.ins.name) != 0 ||
			a.directive.ins.args_count != b.directive.ins.args_count)
			return (false);
		for (size_t i = 0 ; i < a.directive.ins.args_count ; i++)
		{
			if (bstr_cmp(a.directive.ins.args[i], b.directive.ins.args[i]) != 0)
				return (false);
		}
	}
	return (true);
}

static void txt_directive_print_fd(int fd, t_txt_directive directive)
{
	if (directive.type == TXT_DIRECTIVE_TYPE_NONE)
	{
		ft_putstr_fd(fd, "Type: None\n");
	}
	else if (directive.type == TXT_DIRECTIVE_TYPE_INS)
	{
		ft_putstr_fd(fd, "Type: Instruction\n");
		bstr_hexdump_fd(fd, directive.directive.ins.label);
		bstr_hexdump_fd(fd, directive.directive.ins.name);
		for (size_t i = 0 ; i < directive.directive.ins.args_count ; i++)
			bstr_hexdump_fd(fd, directive.directive.ins.args[i]);
	}
	else if (directive.type == TXT_DIRECTIVE_TYPE_META)
	{
		ft_putstr_fd(fd, "Type: Metadata\n");
		bstr_hexdump_fd(fd, directive.directive.meta.name);
		bstr_hexdump_fd(fd, directive.directive.meta.value);
	}
}

void test_file_to_txt_directives()
{
	t_bstr file;
	t_array *txt_directives;
	t_txt_directive got;
	t_txt_directive want;

	// Empty file
	file = str_to_bstr("");
	txt_directives = file_to_txt_directives(file);
	ASSERT(txt_directives->len, ==, 0U);
	ft_array_free(txt_directives);

	// Complete example
	file = str_to_bstr(
		".name \"NAME\"\n"
		".comment \"COMMENT\"\n"
		"\n"
		"# code\n"
		"label: and %42, :label, r16\n"
		"live %42"
	);
	txt_directives = file_to_txt_directives(file);
	ASSERT(txt_directives->len, ==, 4U);
	got = *(t_txt_directive*)ft_array_get(txt_directives, 0);
	want = (t_txt_directive){.type = TXT_DIRECTIVE_TYPE_META,
							 .directive.meta = {
								.name = str_to_bstr("name"),
								.value = str_to_bstr("NAME"),
							},
	};
	ASSERT_OBJ(txt_directive_equal, got, want, == true, txt_directive_print_fd);
	got = *(t_txt_directive*)ft_array_get(txt_directives, 1);
	want = (t_txt_directive){.type = TXT_DIRECTIVE_TYPE_META,
							 .directive.meta = {
								.name = str_to_bstr("comment"),
								.value = str_to_bstr("COMMENT"),
							},
	};
	ASSERT_OBJ(txt_directive_equal, got, want, == true, txt_directive_print_fd);
	got = *(t_txt_directive*)ft_array_get(txt_directives, 2);
	want = (t_txt_directive){.type = TXT_DIRECTIVE_TYPE_INS,
							 .directive.ins = {
								.label = str_to_bstr("label"),
								.name = str_to_bstr("and"),
								.args = {
									str_to_bstr("%42"),
									str_to_bstr(":label"),
									str_to_bstr("r16"),
								},
								.args_count = 3,
							},
	};
	ASSERT_OBJ(txt_directive_equal, got, want, == true, txt_directive_print_fd);
	got = *(t_txt_directive*)ft_array_get(txt_directives, 3);
	want = (t_txt_directive){.type = TXT_DIRECTIVE_TYPE_INS,
							 .directive.ins = {
								.label = str_to_bstr(""),
								.name = str_to_bstr("live"),
								.args = {
									str_to_bstr("%42"),
								},
								.args_count = 1,
							},
	};
	ASSERT_OBJ(txt_directive_equal, got, want, == true, txt_directive_print_fd);
	ft_array_free(txt_directives);
}

void test_line_to_txt_directive()
{
	t_bstr line;
	t_txt_directive got;
	t_txt_directive want;

	// Meta directive
	line = str_to_bstr(".name \"VALUE\"");
	got = line_to_txt_directive(line);
	want = (t_txt_directive){.type = TXT_DIRECTIVE_TYPE_META,
							 .directive.meta = {
								.name = str_to_bstr("name"),
								.value = str_to_bstr("VALUE"),
							}};
	ASSERT_OBJ(txt_directive_equal, got, want, == true, txt_directive_print_fd);

	// Instruction directive
	line = str_to_bstr("label: and %42, :label, r16");
	got = line_to_txt_directive(line);
	want = (t_txt_directive){.type = TXT_DIRECTIVE_TYPE_INS,
							.directive.ins = {
								.label = str_to_bstr("label"),
								.name = str_to_bstr("and"),
								.args = {
									str_to_bstr("%42"),
									str_to_bstr(":label"),
									str_to_bstr("r16"),
								},
								.args_count = 3
							}};
	ASSERT_OBJ(txt_directive_equal, got, want, == true, txt_directive_print_fd);

	// No directive
	line = str_to_bstr("");
	got = line_to_txt_directive(line);
	want = (t_txt_directive){.type = TXT_DIRECTIVE_TYPE_NONE, .directive = {}};
	ASSERT_OBJ(txt_directive_equal, got, want, == true, txt_directive_print_fd);

	// No directive with comment
	line = str_to_bstr(" # comment");
	got = line_to_txt_directive(line);
	want = (t_txt_directive){.type = TXT_DIRECTIVE_TYPE_NONE, .directive = {}};
	ASSERT_OBJ(txt_directive_equal, got, want, == true, txt_directive_print_fd);
	line = str_to_bstr("	 	; comment");
	got = line_to_txt_directive(line);
	want = (t_txt_directive){.type = TXT_DIRECTIVE_TYPE_NONE, .directive = {}};
	ASSERT_OBJ(txt_directive_equal, got, want, == true, txt_directive_print_fd);

	// Meta directive with an empty value
	line = str_to_bstr(".name \"\"");
	got = line_to_txt_directive(line);
	want = (t_txt_directive){.type = TXT_DIRECTIVE_TYPE_META,
							 .directive.meta = {
								.name = str_to_bstr("name"),
								.value = str_to_bstr(""),
							}};
	ASSERT_OBJ(txt_directive_equal, got, want, == true, txt_directive_print_fd);

	// Instruction directive with no label and operands
	line = str_to_bstr("live");
	got = line_to_txt_directive(line);
	want = (t_txt_directive){.type = TXT_DIRECTIVE_TYPE_INS,
							.directive.ins = {
								.label = str_to_bstr(""),
								.name = str_to_bstr("live"),
								.args = {
									str_to_bstr(""),
									str_to_bstr(""),
									str_to_bstr(""),
								},
								.args_count = 0
							}};
	ASSERT_OBJ(txt_directive_equal, got, want, == true, txt_directive_print_fd);
}

void test_ins_set_size()
{
	t_ins ins;

	// Simple example
	ins = str_to_ins("live %42");
	ins_set_size(&ins);
	ASSERT(ins.size, ==, 5U);

	// Instruction with direct value size equals to 2
	ins = str_to_ins("zjmp %42");
	ins_set_size(&ins);
	ASSERT(ins.size, ==, 3U);

	// Instruction with argument coding byte
	ins = str_to_ins("aff r1");
	ins_set_size(&ins);
	ASSERT(ins.size, ==, 3U);

	// Registers only
	ins = str_to_ins("add r1,r2,r3");
	ins_set_size(&ins);
	ASSERT(ins.size, ==, 5U);

	// Biggest instruction
	ins = str_to_ins("or %42, %42, r1");
	ins_set_size(&ins);
	ASSERT(ins.size, ==, 11U);
}

struct ins_set_args_type_test
{
	t_ins_spec	*ins;
	char		bin[1];
	t_arg_type	expected[3];
};

void test_ins_set_args_type()
{
	char *tmp;
	char *tmp_save;
	t_ins ins;

	struct ins_set_args_type_test tests[] =
	{
		// Tests with instructions that have no ACB
		{&(g_instructions[0]), {0b11111111}, {DIR_ARG, NO_ARG, NO_ARG}},
		{&(g_instructions[8]), {0b11111111}, {DIR_ARG, NO_ARG, NO_ARG}},

		// Tests with instructions that have an ACB but with an ACB that has
		// data outside the expected arguments
		{&(g_instructions[15]), {0b01111111}, {REG_ARG, NO_ARG, NO_ARG}},
		{&(g_instructions[15]), {0b10111111}, {DIR_ARG, NO_ARG, NO_ARG}},
		{&(g_instructions[15]), {0b11111111}, {IND_ARG, NO_ARG, NO_ARG}},

		// Tests with instructions that have an ACB and with a proper ACB
		{&(g_instructions[3]), {0b01010100}, {REG_ARG, REG_ARG, REG_ARG}},
		{&(g_instructions[3]), {0b10101000}, {DIR_ARG, DIR_ARG, DIR_ARG}},
		{&(g_instructions[3]), {0b11111100}, {IND_ARG, IND_ARG, IND_ARG}},
		{&(g_instructions[3]), {0b01101100}, {REG_ARG, DIR_ARG, IND_ARG}},
	};

	for (size_t i = 0; i < sizeof(tests)/sizeof(tests[0]); i++)
	{
		bzero(&ins, sizeof(ins));
		ins.instruction = tests[i].ins;
		tmp = &(tests[i].bin[0]);
		tmp_save = tmp;
		ins_set_args_type(&ins, &tmp);
		if (ins.instruction->has_acb)
			ASSERT(tmp, ==, tmp_save + 1);
		ASSERT(ins.args_type[0], ==, (t_arg_type)tests[i].expected[0]);
		ASSERT(ins.args_type[1], ==, (t_arg_type)tests[i].expected[1]);
		ASSERT(ins.args_type[2], ==, (t_arg_type)tests[i].expected[2]);
	}
}

struct ins_args_ok_test
{
	t_ins	input;
	bool		output;
};

void test_ins_args_ok()
{
	struct ins_args_ok_test tests[] =
	{
		// Tests with an instruction with extra arguments
		{{&g_instructions[0], {DIR_ARG, DIR_ARG, DIR_ARG}, {0, 0, 0}, 0}, true},
		{{&g_instructions[0], {REG_ARG, DIR_ARG, DIR_ARG}, {0, 0, 0}, 0}, false},
		{{&g_instructions[0], {IND_ARG, DIR_ARG, DIR_ARG}, {0, 0, 0}, 0}, false},


		// Normal tests
		{{&g_instructions[0], {NO_ARG, NO_ARG, NO_ARG}, {0, 0, 0}, 0}, false},

		{{&g_instructions[3], {REG_ARG, REG_ARG, REG_ARG}, {0, 0, 0}, 0}, true},
		{{&g_instructions[3], {DIR_ARG, REG_ARG, REG_ARG}, {0, 0, 0}, 0}, false},
		{{&g_instructions[3], {REG_ARG, DIR_ARG, REG_ARG}, {0, 0, 0}, 0}, false},
		{{&g_instructions[3], {REG_ARG, REG_ARG, DIR_ARG}, {0, 0, 0}, 0}, false},

		{{&g_instructions[5], {REG_ARG, REG_ARG, REG_ARG}, {0, 0, 0}, 0}, true},
		{{&g_instructions[5], {DIR_ARG, DIR_ARG, REG_ARG}, {0, 0, 0}, 0}, true},
		{{&g_instructions[5], {IND_ARG, IND_ARG, REG_ARG}, {0, 0, 0}, 0}, true},
		{{&g_instructions[5], {DIR_ARG, IND_ARG, REG_ARG}, {0, 0, 0}, 0}, true},
		{{&g_instructions[5], {IND_ARG, DIR_ARG, REG_ARG}, {0, 0, 0}, 0}, true},
		{{&g_instructions[5], {DIR_ARG, REG_ARG, REG_ARG}, {0, 0, 0}, 0}, true},
		{{&g_instructions[5], {REG_ARG, DIR_ARG, REG_ARG}, {0, 0, 0}, 0}, true},
		{{&g_instructions[5], {IND_ARG, REG_ARG, REG_ARG}, {0, 0, 0}, 0}, true},
		{{&g_instructions[5], {REG_ARG, IND_ARG, REG_ARG}, {0, 0, 0}, 0}, true},

		{{&g_instructions[5], {REG_ARG, REG_ARG, DIR_ARG}, {0, 0, 0}, 0}, false},
		{{&g_instructions[5], {REG_ARG, REG_ARG, IND_ARG}, {0, 0, 0}, 0}, false},
		{{&g_instructions[5], {DIR_ARG, DIR_ARG, DIR_ARG}, {0, 0, 0}, 0}, false},
		{{&g_instructions[5], {DIR_ARG, DIR_ARG, IND_ARG}, {0, 0, 0}, 0}, false},
		{{&g_instructions[5], {IND_ARG, IND_ARG, DIR_ARG}, {0, 0, 0}, 0}, false},
		{{&g_instructions[5], {IND_ARG, IND_ARG, IND_ARG}, {0, 0, 0}, 0}, false},

		{{&g_instructions[5], {NO_ARG, NO_ARG, NO_ARG}, {0, 0, 0}, 0}, false},
	};

	for (size_t i = 0; i < sizeof(tests)/sizeof(tests[0]); i++)
	{
		ASSERT(ins_args_ok(&(tests[i].input)), ==, tests[i].output);
	}
}

typedef struct	s_bin_to_ins_test
{
	char	input[INS_MAX_SIZE];
	t_ins	want;
}				t_bin_to_ins_test;

#define UNPACK( ... ) __VA_ARGS__

#define COMPARE_INS(t) \
do { \
	t_bin_to_ins_test test = UNPACK(t); \
	got = bin_to_ins(test.input); \
	ASSERT_OBJ(ins_equal, &test.want, &got, == true, ins_print); \
} while (0)

void test_bin_to_ins()
{
	t_ins got;

	COMPARE_INS(((t_bin_to_ins_test){
		{0x01, 0x01, 0x02, 0x03, 0x04},
		{&(g_instructions[0]), {DIR_ARG, NO_ARG, NO_ARG}, {0x01020304, 0x00, 0x00}, 5}
	}));
	COMPARE_INS(((t_bin_to_ins_test){
		{0x02, 0b10010000, 0x01, 0x02, 0x03, 0x04, 0x05},
		{&(g_instructions[1]), {DIR_ARG, REG_ARG, NO_ARG}, {0x01020304, 0x05, 0x00}, 7}
	}));
	COMPARE_INS(((t_bin_to_ins_test){
		{0x02, 0b11010000, 0x01, 0x02, 0x03},
		{&(g_instructions[1]), {IND_ARG, REG_ARG, NO_ARG}, {0x0102, 0x03, 0x00}, 5}
	}));
	// Examples from the PDF
	COMPARE_INS(((t_bin_to_ins_test){
		{0x0b, 0x68, 0x01, 0x00, 0x0f, 0x00, 0x01},
		{&(g_instructions[10]), {REG_ARG, DIR_ARG, DIR_ARG}, {0x01, 0x000f, 0x0001}, 7}
	}));
	COMPARE_INS(((t_bin_to_ins_test){
		{0x06, 0x64, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01},
		{&(g_instructions[5]), {REG_ARG, DIR_ARG, REG_ARG}, {0x01, 0x00000000, 0x01}, 8}
	}));
	COMPARE_INS(((t_bin_to_ins_test){
		{0x01, 0x00, 0x00, 0x00, 0x01},
		{&(g_instructions[0]), {DIR_ARG, NO_ARG, NO_ARG}, {0x00000001, 0x00, 0x00}, 5}
	}));
	COMPARE_INS(((t_bin_to_ins_test){
		{0x09, 0xff, 0xfb},
		{&(g_instructions[8]), {DIR_ARG, NO_ARG, NO_ARG}, {0xfffb, 0x00, 0x00}, 3}
	}));
	// Register argument is too big
	COMPARE_INS(((t_bin_to_ins_test){
		{0x10, 0b01000000, 0x11},
		{NULL, {0, 0, 0}, {0, 0, 0}, 0}
	}));
	// Register argument is too small
	COMPARE_INS(((t_bin_to_ins_test){
		{0x10, 0b01000000, 0x00},
		{NULL, {0, 0, 0}, {0, 0, 0}, 0}
	}));
}

void test_txt_to_txt_meta()
{
	t_bstr txt;
	t_bstr got;
	t_bstr want;
	t_txt_meta txt_meta;

	// Simple example
	txt = str_to_bstr(".name \"NAME\"");
	txt_meta = txt_to_txt_meta(txt);
	got = txt_meta.name;
	want = str_to_bstr("name");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_meta.value;
	want = str_to_bstr("NAME");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);

	// Null byte in value
	txt = (t_bstr){".name \"NA\x00ME\"", 14};
	txt_meta = txt_to_txt_meta(txt);
	got = txt_meta.name;
	want = str_to_bstr("name");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	ASSERT(txt_meta.value.len, ==, 5U);
	ASSERT(txt_meta.value.str[2], ==, 0);

	// Empty value
	txt = str_to_bstr(".name \"\"");
	txt_meta = txt_to_txt_meta(txt);
	got = txt_meta.name;
	want = str_to_bstr("name");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_meta.value;
	want = str_to_bstr("");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);

	/* Syntax warnings test cases */
	// Missing dot
	txt = str_to_bstr("name \"NAME\"");
	txt_meta = txt_to_txt_meta(txt);
	got = txt_meta.name;
	want = str_to_bstr("name");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_meta.value;
	want = str_to_bstr("NAME");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);

	// Missing value
	txt = str_to_bstr(".name");
	txt_meta = txt_to_txt_meta(txt);
	got = txt_meta.name;
	want = str_to_bstr("name");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_meta.value;
	want = str_to_bstr("");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);

	// Missing whitespace between name and value
	txt = str_to_bstr(".name\"NAME\"");
	txt_meta = txt_to_txt_meta(txt);
	got = txt_meta.name;
	want = str_to_bstr("name");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_meta.value;
	want = str_to_bstr("NAME");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);

	// Missing opening and closing quotes
	txt = str_to_bstr(".name NAME");
	txt_meta = txt_to_txt_meta(txt);
	got = txt_meta.name;
	want = str_to_bstr("name");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_meta.value;
	want = str_to_bstr("NAME");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);

	// Garbage
	txt = str_to_bstr(".name \"NAME\" garbage");
	txt_meta = txt_to_txt_meta(txt);
	got = txt_meta.name;
	want = str_to_bstr("name");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_meta.value;
	want = str_to_bstr("NAME");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);

	// Multiple syntax warnings
	txt = str_to_bstr("name\"NAME");
	txt_meta = txt_to_txt_meta(txt);
	got = txt_meta.name;
	want = str_to_bstr("name");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_meta.value;
	want = str_to_bstr("NAME");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);

	// Multiple syntax warnings
	txt = str_to_bstr("name NAME");
	txt_meta = txt_to_txt_meta(txt);
	got = txt_meta.name;
	want = str_to_bstr("name");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_meta.value;
	want = str_to_bstr("NAME");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
}

void test_txt_to_txt_ins()
{
	t_bstr txt;
	t_bstr got;
	t_bstr want;
	t_txt_ins txt_ins;

	// Simple example
	txt = str_to_bstr("label: live %42");
	txt_ins = txt_to_txt_ins(txt);
	got = txt_ins.label;
	want = str_to_bstr("label");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_ins.name;
	want = str_to_bstr("live");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	ASSERT(txt_ins.args_count, ==, 1U);
	got = txt_ins.args[0];
	want = str_to_bstr("%42");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);

	// Label only
	txt = str_to_bstr("label:");
	txt_ins = txt_to_txt_ins(txt);
	got = txt_ins.label;
	want = str_to_bstr("label");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	ASSERT(txt_ins.name.len, ==, 0U);
	ASSERT(txt_ins.args_count, ==, 0U);

	// Two operands
	txt = str_to_bstr("lld %-42, r16");
	txt_ins = txt_to_txt_ins(txt);
	got = txt_ins.name;
	want = str_to_bstr("lld");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	ASSERT(txt_ins.args_count, ==, 2U);
	got = txt_ins.args[0];
	want = str_to_bstr("%-42");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_ins.args[1];
	want = str_to_bstr("r16");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);

	// Three operands
	txt = str_to_bstr("add r1, r2, r3");
	txt_ins = txt_to_txt_ins(txt);
	got = txt_ins.name;
	want = str_to_bstr("add");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	ASSERT(txt_ins.args_count, ==, 3U);
	got = txt_ins.args[0];
	want = str_to_bstr("r1");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_ins.args[1];
	want = str_to_bstr("r2");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_ins.args[2];
	want = str_to_bstr("r3");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);

	// Three operands and no whitespaces between them
	txt = str_to_bstr("add r1,r2,r3");
	txt_ins = txt_to_txt_ins(txt);
	got = txt_ins.name;
	want = str_to_bstr("add");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	ASSERT(txt_ins.args_count, ==, 3U);
	got = txt_ins.args[0];
	want = str_to_bstr("r1");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_ins.args[1];
	want = str_to_bstr("r2");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_ins.args[2];
	want = str_to_bstr("r3");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);

	// Three operands and lots of whitespaces between them
	txt = str_to_bstr("add r1\t \t, \t r2  ,\t\tr3");
	txt_ins = txt_to_txt_ins(txt);
	got = txt_ins.name;
	want = str_to_bstr("add");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	ASSERT(txt_ins.args_count, ==, 3U);
	got = txt_ins.args[0];
	want = str_to_bstr("r1");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_ins.args[1];
	want = str_to_bstr("r2");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_ins.args[2];
	want = str_to_bstr("r3");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);

	// No label and operands
	txt = str_to_bstr("live");
	txt_ins = txt_to_txt_ins(txt);
	got = txt_ins.label;
	want = str_to_bstr("");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_ins.name;
	want = str_to_bstr("live");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	ASSERT(txt_ins.args_count, ==, 0U);
	got = txt_ins.args[0];
	want = str_to_bstr("");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_ins.args[1];
	want = str_to_bstr("");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_ins.args[2];
	want = str_to_bstr("");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);

	/* Syntax warnings test cases */
	// Missing whitespace between label and instruction name
	txt = str_to_bstr("label:live %42");
	txt_ins = txt_to_txt_ins(txt);
	got = txt_ins.label;
	want = str_to_bstr("label");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_ins.name;
	want = str_to_bstr("live");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	ASSERT(txt_ins.args_count, ==, 1U);
	got = txt_ins.args[0];
	want = str_to_bstr("%42");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_ins.args[1];
	want = str_to_bstr("");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_ins.args[2];
	want = str_to_bstr("");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);

	// Garbage
	txt = str_to_bstr("add r1, r2, r3 garbage");
	txt_ins = txt_to_txt_ins(txt);
	got = txt_ins.label;
	want = str_to_bstr("");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_ins.name;
	want = str_to_bstr("add");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	ASSERT(txt_ins.args_count, ==, 3U);
	got = txt_ins.args[0];
	want = str_to_bstr("r1");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_ins.args[1];
	want = str_to_bstr("r2");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
	got = txt_ins.args[2];
	want = str_to_bstr("r3");
	ASSERT_OBJ(bstr_cmp, got, want, == 0, bstr_hexdump_fd);
}

void test_txt_ins_to_ins()
{
	t_bstr txt;
	t_txt_ins txt_ins;
	t_ins got;
	t_ins want;

	// Simple live example
	txt = str_to_bstr("live %-42");
	txt_ins = txt_to_txt_ins(txt);
	got = txt_ins_to_ins(txt_ins);
	want = (t_ins){&g_instructions[0], {DIR_ARG}, {-42}, 5};
	ASSERT_OBJ(ins_equal, &got, &want, == true, ins_print);

	// Simple aff example
	txt = str_to_bstr("aff r16");
	txt_ins = txt_to_txt_ins(txt);
	got = txt_ins_to_ins(txt_ins);
	want = (t_ins){&g_instructions[15], {REG_ARG}, {16}, 3};
	ASSERT_OBJ(ins_equal, &got, &want, == true, ins_print);

	// All three types of arguments
	txt = str_to_bstr("and %-42, -42, r16");
	txt_ins = txt_to_txt_ins(txt);
	got = txt_ins_to_ins(txt_ins);
	want = (t_ins){&g_instructions[5], {DIR_ARG, IND_ARG, REG_ARG}, {-42, -42, 16}, 9};
	ASSERT_OBJ(ins_equal, &got, &want, == true, ins_print);

	// Minimum direct and indirect values
	txt = str_to_bstr("and %-2147483648, -32768, r16");
	txt_ins = txt_to_txt_ins(txt);
	got = txt_ins_to_ins(txt_ins);
	want = (t_ins){&g_instructions[5], {DIR_ARG, IND_ARG, REG_ARG}, {-2147483648, -32768, 16}, 9};
	ASSERT_OBJ(ins_equal, &got, &want, == true, ins_print);

	// Maximum direct and indirect values
	txt = str_to_bstr("and %2147483647, 32767, r16");
	txt_ins = txt_to_txt_ins(txt);
	got = txt_ins_to_ins(txt_ins);
	want = (t_ins){&g_instructions[5], {DIR_ARG, IND_ARG, REG_ARG}, {2147483647, 32767, 16}, 9};
	ASSERT_OBJ(ins_equal, &got, &want, == true, ins_print);

	// With labels
	txt = str_to_bstr("and %:label, :label, r16");
	txt_ins = txt_to_txt_ins(txt);
	got = txt_ins_to_ins(txt_ins);
	want = (t_ins){&g_instructions[5], {DIR_ARG, IND_ARG, REG_ARG}, {0, 0, 16}, 9};
	ASSERT_OBJ(ins_equal, &got, &want, == true, ins_print);

	// With labels longer than DIRECT_VALUE_MAX_LEN
	txt = str_to_bstr("and %:very_long_label, :very_long_label, r16");
	txt_ins = txt_to_txt_ins(txt);
	got = txt_ins_to_ins(txt_ins);
	want = (t_ins){&g_instructions[5], {DIR_ARG, IND_ARG, REG_ARG}, {0, 0, 16}, 9};
	ASSERT_OBJ(ins_equal, &got, &want, == true, ins_print);

	// Label only
	txt = str_to_bstr("label:");
	txt_ins = txt_to_txt_ins(txt);
	got = txt_ins_to_ins(txt_ins);
	want = (t_ins){NULL, {NO_ARG, NO_ARG, NO_ARG}, {0, 0, 0}, 0};
	ASSERT_OBJ(ins_equal, &got, &want, == true, ins_print);
}

void test_ins_to_bin_ins()
{
	t_ins ins;
	t_bin_ins got;
	t_bin_ins want;

	// Simple example
	ins = str_to_ins("live %42");
	got = ins_to_bin_ins(&ins);
	want = (t_bin_ins){{0x01, 0x00, 0x00, 0x00, 0x2a}, 5U};
	ASSERT(got.len, ==, want.len);
	ASSERT_NOBJ(memcmp, &got.bin, &want.bin, got.len, == 0, ft_hexdump_fd);

	// Negative direct value
	ins = str_to_ins("live %-2147483648");
	got = ins_to_bin_ins(&ins);
	want = (t_bin_ins){{0x01, 0x80, 0x00, 0x00, 0x00}, 5U};
	ASSERT(got.len, ==, want.len);
	ASSERT_NOBJ(memcmp, &got.bin, &want.bin, got.len, == 0, ft_hexdump_fd);

	// All three types of arguments
	ins = str_to_ins("and %-42, -42, r16");
	got = ins_to_bin_ins(&ins);
	want = (t_bin_ins){{0x06, 0b10110100, 0xff, 0xff, 0xff, 0xd6, 0xff, 0xd6, 0x10}, 9U};
	ASSERT(got.len, ==, want.len);
	ASSERT_NOBJ(memcmp, &got.bin, &want.bin, got.len, == 0, ft_hexdump_fd);

	// Direct argument size is 2
	ins = str_to_ins("sti %-42, -42, r1");
	got = ins_to_bin_ins(&ins);
	want = (t_bin_ins){{0x0b, 0b10110100, 0xff, 0xd6, 0xff, 0xd6, 0x01}, 7U};
	ASSERT(got.len, ==, want.len);
	ASSERT_NOBJ(memcmp, &got.bin, &want.bin, got.len, == 0, ft_hexdump_fd);

	// Label only
	ins = str_to_ins("label:");
	got = ins_to_bin_ins(&ins);
	want = (t_bin_ins){{0x00, 0b00000000, 0x00, 0x00, 0x00, 0x00, 0x00}, 0U};
	ASSERT(got.len, ==, want.len);
	ASSERT_NOBJ(memcmp, &got.bin, &want.bin, got.len, == 0, ft_hexdump_fd);
}

void test_ins_to_str()
{
	char *got;
	char *want;
	t_ins ins;

	// Simple test
	want = "live %42";
	ins = str_to_ins(want);
	got = ins_to_str(ins);
	ASSERT_OBJ(strcmp, got, want, == 0, ft_putstr_fd);

	// With three operands and three different types
	want = "add %42, 42, r16";
	ins = str_to_ins(want);
	got = ins_to_str(ins);
	ASSERT_OBJ(strcmp, got, want, == 0, ft_putstr_fd);

	// With no instruction
	ins = str_to_ins("label:");
	got = ins_to_str(ins);
	ASSERT_OBJ(strcmp, got, "", == 0, ft_putstr_fd);
}

void test_get_prog_header()
{
	char buffer[sizeof(t_prog_header)] = {0x00, 0xea, 0x83, 0xf3};
	t_prog_header header;
	size_t index;

	ASSERT(get_prog_header(buffer, sizeof(t_prog_header) - 1, &header), ==,
		(t_error)ERR_PROG_HEADER_TOO_SMALL);

	index = sizeof(header.magic_number);

	// Magic number test
	ASSERT(get_prog_header(buffer, sizeof(t_prog_header), &header), ==,
		(t_error)ERR_OK);
	ASSERT(header.magic_number, ==, 0x00ea83f3U);

	// Name test
	for (size_t i = 0; i < PROG_NAME_LENGTH; i++)
		buffer[index + i] = i + 1;
	ASSERT(get_prog_header(buffer, sizeof(t_prog_header), &header), ==,
		(t_error)ERR_OK);
	for (size_t i = 0; i < PROG_NAME_LENGTH; i++)
		ASSERT(header.name[i], ==, i + 1);
	index += PROG_NAME_LENGTH;

	// Size test
	buffer[index + 0] = 0x01;
	buffer[index + 1] = 0x02;
	buffer[index + 2] = 0x03;
	buffer[index + 3] = 0x04;
	buffer[index + 4] = 0x05;
	buffer[index + 5] = 0x06;
	buffer[index + 6] = 0x07;
	buffer[index + 7] = 0x08;
	ASSERT(get_prog_header(buffer, sizeof(t_prog_header), &header), ==,
		(t_error)ERR_OK);
	ASSERT(header.size, ==, 0x0102030405060708ULL);
	index += sizeof(header.size);

	// Comment test
	for (size_t i = 0; i < PROG_COMMENT_LENGTH; i++)
		buffer[index + i] = (i + 1) % 256;
	ASSERT(get_prog_header(buffer, sizeof(t_prog_header), &header), ==,
		(t_error)ERR_OK);
	for (size_t i = 0; i < PROG_COMMENT_LENGTH; i++)
		ASSERT(header.comment[i], ==, (i + 1) % 256);

	// Wrong magic number test
	buffer[3] = 0xf4;
	ASSERT(get_prog_header(buffer, sizeof(t_prog_header), &header), ==,
		(t_error)ERR_PROG_HEADER_WRONG_MAGIC_NUMBER);
}

void test_txt_ins_get_ins_spec()
{
	t_txt_ins txt_ins;
	t_ins_spec *got;
	t_ins_spec *want;

	// First instruction
	txt_ins = txt_to_txt_ins(str_to_bstr("live %42"));
	got = txt_ins_get_ins_spec(txt_ins);
	want = &g_instructions[0];
	ASSERT(got, ==, want);

	// Last instruction
	txt_ins = txt_to_txt_ins(str_to_bstr("aff r1"));
	got = txt_ins_get_ins_spec(txt_ins);
	want = &g_instructions[15];
	ASSERT(got, ==, want);

	// NULL
	txt_ins = txt_to_txt_ins(str_to_bstr("unknown %42"));
	got = txt_ins_get_ins_spec(txt_ins);
	want = NULL;
	ASSERT(got, ==, want);
}

int parse_error_equal(t_parse_error a, t_parse_error b)
{
	if (a.column)
		return (a.type == b.type
				&& a.msg == b.msg
				&& bstr_cmp(a.line, b.line) == 0
				&& a.line_num == b.line_num
				&& a.column == b.column
				&& a.len == b.len);
	else
		return (a.type == b.type
				&& a.msg == b.msg);
}

void parse_error_print_fd(int fd, t_parse_error error)
{
	parse_error_print(fd, &error, NULL);
}

typedef struct	s_check_syntax_file_test
{
	t_bstr			file;
	size_t			errors_count;
	t_parse_error	want[10];
}				t_check_syntax_file_test;

#define COMPARE_SYNTAX_ERRORS(t) \
do { \
	t_check_syntax_file_test test = UNPACK(t); \
	errors = check_syntax_file(test.file); \
	ASSERT(errors->len, ==, test.errors_count); \
	for (size_t i = 0; i < errors->len; i++) \
	{ \
		got = *(t_parse_error*)ft_array_get(errors, i); \
		want = test.want[i]; \
		ASSERT_OBJ(parse_error_equal, got, want, == true, parse_error_print_fd); \
	} \
	ft_array_free(errors); \
} while (0)

t_bstr bstr_get_line(t_bstr str, size_t index)
{
	t_bstr line;

	for (size_t i = 0; i <= index; i++)
	{
		line = bstr_read_until(&str, "\n");
		bstr_skip_char(&str, '\n');
	}
	return (line);
}

void test_check_syntax_file()
{
	t_array *errors;
	t_parse_error got;
	t_parse_error want;

	// Metadata tests
	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("name \"NAME\""),
		1,
		{{P_ERR_TYPE_WARNING, P_ERR_MSG_META_MISS_DOT,
			test.file, 1U, test.file.str + 0, 0}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr(".name "),
		1,
		{{P_ERR_TYPE_WARNING, P_ERR_MSG_META_MISS_VALUE,
			test.file, 1U, test.file.str + 5, 0}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr(".name\"NAME\""),
		1,
		{{P_ERR_TYPE_WARNING, P_ERR_MSG_META_MISS_WSP_BETWEEN_NAME_AND_VALUE,
			test.file, 1U, test.file.str + 5, 0}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr(".na0me \"NAME\""),
		1,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			test.file, 1U, test.file.str + 3, 1}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr(". \"NAME\""),
		1,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_META_MISS_NAME,
			test.file, 1U, test.file.str + 1, 0}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr(".name NAME\""),
		1,
		{{P_ERR_TYPE_WARNING, P_ERR_MSG_META_MISS_OPEN_QUOTE,
			test.file, 1U, test.file.str + 6, 0}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr(".name \"NAME"),
		1,
		{{P_ERR_TYPE_WARNING, P_ERR_MSG_META_MISS_CLOSE_QUOTE,
			test.file, 1U, test.file.str + 11, 0}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr(".name \"NAME\" garbage"),
		1,
		{{P_ERR_TYPE_WARNING, P_ERR_MSG_META_GARBAGE,
			test.file, 1U, test.file.str + 12, 8}}
	}));

	// No errors test
	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr(".name \"NAME\""),
		0,
		{}
	}));


	// Instructions tests
	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("la+el: live %42"),
		1,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			test.file, 1U, test.file.str + 2, 1}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr(": live %42"),
		1,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_MISS_LABEL_NAME,
			test.file, 1U, test.file.str + 0, 1}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("label:live %42"),
		1,
		{{P_ERR_TYPE_WARNING, P_ERR_MSG_INS_MISS_WSP_BETWEEN_LABEL_AND_INSTRUCTION,
			test.file, 1U, test.file.str + 6, 0}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("label: , r1"),
		2,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_MISS_NAME,
			test.file, 1U, test.file.str + 7, 0},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_EMPTY_OPERAND,
			test.file, 1U, test.file.str + 7, 0}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("label: live, r1"),
		1,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_EMPTY_OPERAND,
			test.file, 1U, test.file.str + 11, 0}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("live %42 %42 %42"),
		2,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_MISS_COMMA,
			test.file, 1U, test.file.str + 8, 0},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_MISS_COMMA,
			test.file, 1U, test.file.str + 12, 0}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("live , ,"),
		3,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_EMPTY_OPERAND,
			test.file, 1U, test.file.str + 5, 0},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_EMPTY_OPERAND,
			test.file, 1U, test.file.str + 7, 0},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_EMPTY_OPERAND,
			test.file, 1U, test.file.str + 8, 0}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("live r, r, r"),
		3,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_MISS_REGISTER_NUMBER,
			test.file, 1U, test.file.str + 5, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_MISS_REGISTER_NUMBER,
			test.file, 1U, test.file.str + 8, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_MISS_REGISTER_NUMBER,
			test.file, 1U, test.file.str + 11, 1}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("live r111111111111, r111111111111, r111111111111"),
		3,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_VALUE_LEN,
			test.file, 1U, test.file.str + 6, 12},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_VALUE_LEN,
			test.file, 1U, test.file.str + 21, 12},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_VALUE_LEN,
			test.file, 1U, test.file.str + 36, 12}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("live r1_6, r1_6, r1_6"),
		3,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			test.file, 1U, test.file.str + 7, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			test.file, 1U, test.file.str + 13, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			test.file, 1U, test.file.str + 19, 1}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("live %, %, %"),
		3,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_MISS_DIRECT_VALUE,
			test.file, 1U, test.file.str + 5, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_MISS_DIRECT_VALUE,
			test.file, 1U, test.file.str + 8, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_MISS_DIRECT_VALUE,
			test.file, 1U, test.file.str + 11, 1}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("live %:, %:, %:"),
		3,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_MISS_LABEL_REF,
			test.file, 1U, test.file.str + 6, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_MISS_LABEL_REF,
			test.file, 1U, test.file.str + 10, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_MISS_LABEL_REF,
			test.file, 1U, test.file.str + 14, 1}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("live %:la+el, %:la+el, %:la+el"),
		3,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			test.file, 1U, test.file.str + 9, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			test.file, 1U, test.file.str + 18, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			test.file, 1U, test.file.str + 27, 1}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("live %111111111111, %111111111111, %111111111111"),
		3,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_VALUE_LEN,
			test.file, 1U, test.file.str + 6, 12},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_VALUE_LEN,
			test.file, 1U, test.file.str + 21, 12},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_VALUE_LEN,
			test.file, 1U, test.file.str + 36, 12}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("live %1_6, %1_6, %1_6"),
		3,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			test.file, 1U, test.file.str + 7, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			test.file, 1U, test.file.str + 13, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			test.file, 1U, test.file.str + 19, 1}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("live :, :, :"),
		3,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_MISS_LABEL_REF,
			test.file, 1U, test.file.str + 5, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_MISS_LABEL_REF,
			test.file, 1U, test.file.str + 8, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_MISS_LABEL_REF,
			test.file, 1U, test.file.str + 11, 1}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("live :la+el, :la+el, :la+el"),
		3,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			test.file, 1U, test.file.str + 8, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			test.file, 1U, test.file.str + 16, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			test.file, 1U, test.file.str + 24, 1}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("live 111111111111, 111111111111, 111111111111"),
		3,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_VALUE_LEN,
			test.file, 1U, test.file.str + 5, 12},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_VALUE_LEN,
			test.file, 1U, test.file.str + 19, 12},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_VALUE_LEN,
			test.file, 1U, test.file.str + 33, 12}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("live 1_6, 1_6, 1_6"),
		3,
		{{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			test.file, 1U, test.file.str + 6, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			test.file, 1U, test.file.str + 11, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			test.file, 1U, test.file.str + 16, 1}}
	}));

	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("live %42, %42, %42 garbage"),
		1,
		{{P_ERR_TYPE_WARNING, P_ERR_MSG_INS_GARBAGE,
			test.file, 1U, test.file.str + 18, 8}}
	}));

	// No errors test
	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("label: add r1, r1, r1 # comment"),
		0,
		{}
	}));

	// Test with 11 chars in value
	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("live %-1111111111"),
		0,
		{{}}
	}));


	// No errors test
	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr(".name \"NAME\"\n"
					".comment \"COMMENT\"\n"
					"\n"
					"# instructions\n"
					"; instructions\n"
					"	label:	 	\n"
					" label: add r1, r1, r1 # comment\n"
					"	label:	live	%42 ; comment\n"),
		0,
		{{}}
	}));

	// Multiple errors test
	COMPARE_SYNTAX_ERRORS(((t_check_syntax_file_test){
		str_to_bstr("name NAME\" garbage\n"
					".\"COMMENT \n"
					"\n"
					" unknown_instruction # instructions\n"
					" la+el: add r_, %,  # comment\n"),
		10,
		{{P_ERR_TYPE_WARNING, P_ERR_MSG_META_MISS_DOT,
			bstr_get_line(test.file, 0), 1U, bstr_get_line(test.file, 0).str + 0, 0},
		{P_ERR_TYPE_WARNING, P_ERR_MSG_META_MISS_OPEN_QUOTE,
			bstr_get_line(test.file, 0), 1U, bstr_get_line(test.file, 0).str + 5, 0},
		{P_ERR_TYPE_WARNING, P_ERR_MSG_META_GARBAGE,
			bstr_get_line(test.file, 0), 1U, bstr_get_line(test.file, 0).str + 10, 8},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_META_MISS_NAME,
			bstr_get_line(test.file, 1), 2U, bstr_get_line(test.file, 1).str + 1, 0},
		{P_ERR_TYPE_WARNING, P_ERR_MSG_META_MISS_WSP_BETWEEN_NAME_AND_VALUE,
			bstr_get_line(test.file, 1), 2U, bstr_get_line(test.file, 1).str + 1, 0},
		{P_ERR_TYPE_WARNING, P_ERR_MSG_META_MISS_CLOSE_QUOTE,
			bstr_get_line(test.file, 1), 2U, bstr_get_line(test.file, 1).str + 9, 0},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			bstr_get_line(test.file, 4), 5U, bstr_get_line(test.file, 4).str + 3, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_FORBIDDEN_CHAR,
			bstr_get_line(test.file, 4), 5U, bstr_get_line(test.file, 4).str + 13, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_MISS_DIRECT_VALUE,
			bstr_get_line(test.file, 4), 5U, bstr_get_line(test.file, 4).str + 16, 1},
		{P_ERR_TYPE_ERROR, P_ERR_MSG_INS_EMPTY_OPERAND,
			bstr_get_line(test.file, 4), 5U, bstr_get_line(test.file, 4).str + 18, 0},}
	}));
}

t_array *get_errors(t_bstr file)
{
	t_array *txt_directives;
	t_array *errors;

	txt_directives = file_to_txt_directives(file);
	errors = check_semantic_txt_directives(txt_directives);
	ft_array_free(txt_directives);
	return (errors);
}

#define ERROR_CMP(errors, index, error) \
	do { \
		t_parse_error got = *(t_parse_error*)ft_array_get(errors, index); \
		t_parse_error want = UNPACK(error);							\
		ASSERT_OBJ(parse_error_equal, got, want, == true, parse_error_print_fd); \
	} while (0)

void test_check_semantic_txt_directives()
{
	t_bstr file;
	size_t i;
	t_array *errors;
	char *buffer;

	// Metadata tests
	buffer = malloc(PROG_NAME_LENGTH + PROG_COMMENT_LENGTH + 100);
	buffer[0] = '\0';
	ft_strcat(buffer, ".name \"");
	for (i = 0; i < PROG_NAME_LENGTH; i++)
		ft_strcat(buffer, "N");
	ft_strcat(buffer, "\"\n"
					".comment \"");
	for (i = 0; i < PROG_COMMENT_LENGTH; i++)
		ft_strcat(buffer, "C");
	ft_strcat(buffer, "\"\n");
	file = str_to_bstr(buffer);
	errors = get_errors(file);
	ASSERT(errors->len, ==, 0U);
	ft_array_free(errors);

	buffer[0] = '\0';
	ft_strcat(buffer, ".name \"");
	for (i = 0; i < PROG_NAME_LENGTH + 1; i++)
		ft_strcat(buffer, "N");
	ft_strcat(buffer, "\"\n"
					".comment \"");
	for (i = 0; i < PROG_COMMENT_LENGTH + 1; i++)
		ft_strcat(buffer, "C");
	ft_strcat(buffer, "\"\n");
	file = str_to_bstr(buffer);
	errors = get_errors(file);
	ASSERT(errors->len, ==, 2U);
	i = 0;
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_WARNING, P_ERR_MSG_META_TOO_LONG_NAME_DIRECTIVE,
			bstr_get_line(file, 0), 1U, bstr_get_line(file, 0).str + 7, PROG_NAME_LENGTH + 1}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_WARNING, P_ERR_MSG_META_TOO_LONG_COMMENT_DIRECTIVE,
			bstr_get_line(file, 1), 2U, bstr_get_line(file, 1).str + 10, PROG_COMMENT_LENGTH + 1}));
	ft_array_free(errors);
	free(buffer);

	file = str_to_bstr(".name \"NAME\"\n"
						".comment \"COMMENT\"\n"
						".unknown \"UNKNOWN\"\n");
	errors = get_errors(file);
	ASSERT(errors->len, ==, 1U);
	i = 0;
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_WARNING, P_ERR_MSG_META_DIRECTIVE_UNKNOWN,
			bstr_get_line(file, 2), 3U, bstr_get_line(file, 2).str + 1, 7}));
	ft_array_free(errors);

	file = str_to_bstr(".name \"NAME\"\n"
						".name \"NAME\"\n"
						".comment \"COMMENT\"\n"
						".comment \"COMMENT\"\n"
						".unknown \"UNKNOWN\"\n"
						".unknown \"UNKNOWN\"\n");
	errors = get_errors(file);
	ASSERT(errors->len, ==, 4U);
	i = 0;
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_WARNING, P_ERR_MSG_META_DIRECTIVE_DUPLICATE,
			bstr_get_line(file, 1), 2U, bstr_get_line(file, 1).str + 1, 4}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_WARNING, P_ERR_MSG_META_DIRECTIVE_DUPLICATE,
			bstr_get_line(file, 3), 4U, bstr_get_line(file, 3).str + 1, 7}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_WARNING, P_ERR_MSG_META_DIRECTIVE_UNKNOWN,
			bstr_get_line(file, 4), 5U, bstr_get_line(file, 4).str + 1, 7}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_WARNING, P_ERR_MSG_META_DIRECTIVE_UNKNOWN,
			bstr_get_line(file, 5), 6U, bstr_get_line(file, 5).str + 1, 7}));
	ft_array_free(errors);

	file = str_to_bstr(".unknown \"UNKNOWN\"\n");
	errors = get_errors(file);
	ASSERT(errors->len, ==, 3U);
	i = 0;
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_WARNING, P_ERR_MSG_META_DIRECTIVE_UNKNOWN,
			bstr_get_line(file, 0), 1U, bstr_get_line(file, 0).str + 1, 7}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_WARNING, P_ERR_MSG_META_MISS_DIRECTIVE_NAME,
			bstr_get_line(file, 0), 1U, NULL, 0}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_WARNING, P_ERR_MSG_META_MISS_DIRECTIVE_COMMENT,
			bstr_get_line(file, 0), 1U, NULL, 0}));
	ft_array_free(errors);

	// Instructions tests
	file = str_to_bstr("unknown r20\n");
	errors = get_errors(file);
	ASSERT(errors->len, ==, 3U);
	i = 0;
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_UNKNOWN,
			bstr_get_line(file, 0), 1U, bstr_get_line(file, 0).str + 0, 7}));
	ft_array_free(errors);

	file = str_to_bstr("live %42, %42\n"
					   "add r1\n");
	errors = get_errors(file);
	ASSERT(errors->len, ==, 4U);
	i = 0;
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_WRONG_OPERANDS_COUNT,
			bstr_get_line(file, 0), 1U, bstr_get_line(file, 0).str + 4, 9}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_WRONG_OPERANDS_COUNT,
			bstr_get_line(file, 1), 2U, bstr_get_line(file, 1).str + 3, 3}));
	ft_array_free(errors);

	file = str_to_bstr("add %42, 42, -42\n"
					   "live r1\n"
					   "live 42\n");
	errors = get_errors(file);
	ASSERT(errors->len, ==, 7U);
	i = 0;
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_FORBID_DIR_ARG,
			bstr_get_line(file, 0), 1U, bstr_get_line(file, 0).str + 4, 3}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_FORBID_IND_ARG,
			bstr_get_line(file, 0), 1U, bstr_get_line(file, 0).str + 9, 2}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_FORBID_IND_ARG,
			bstr_get_line(file, 0), 1U, bstr_get_line(file, 0).str + 13, 3}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_FORBID_REG_ARG,
			bstr_get_line(file, 1), 2U, bstr_get_line(file, 1).str + 5, 2}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_FORBID_IND_ARG,
			bstr_get_line(file, 2), 3U, bstr_get_line(file, 2).str + 5, 2}));
	ft_array_free(errors);

	file = str_to_bstr("live %-2147483649\n"
					   "live %2147483648\n"
					   "lfork %-32769\n"
					   "lfork %32768\n"
					   "ld -32769, r16\n"
					   "ld 32768, r16\n");
	errors = get_errors(file);
	ASSERT(errors->len, ==, 8U);
	i = 0;
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_VAL_INT_MIN,
			bstr_get_line(file, 0), 1U, bstr_get_line(file, 0).str + 6, 11}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_VAL_INT_MAX,
			bstr_get_line(file, 1), 2U, bstr_get_line(file, 1).str + 6, 10}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_VAL_SHRT_MIN,
			bstr_get_line(file, 2), 3U, bstr_get_line(file, 2).str + 7, 6}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_VAL_SHRT_MAX,
			bstr_get_line(file, 3), 4U, bstr_get_line(file, 3).str + 7, 5}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_VAL_SHRT_MIN,
			bstr_get_line(file, 4), 5U, bstr_get_line(file, 4).str + 3, 6}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_VAL_SHRT_MAX,
			bstr_get_line(file, 5), 6U, bstr_get_line(file, 5).str + 3, 5}));
	ft_array_free(errors);

	file = str_to_bstr("aff r0\n"
						"aff r17\n");
	errors = get_errors(file);
	ASSERT(errors->len, ==, 4U);
	i = 0;
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_INVALID_REGISTER,
			bstr_get_line(file, 0), 1U, bstr_get_line(file, 0).str + 5, 1}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_INVALID_REGISTER,
			bstr_get_line(file, 1), 2U, bstr_get_line(file, 1).str + 5, 2}));
	ft_array_free(errors);

	file = str_to_bstr("label: live %:label\n"
						"label2: live %:label2\n"
						"label: live %:label\n"
						"label2: live %:label2\n");
	errors = get_errors(file);
	ASSERT(errors->len, ==, 4U);
	i = 0;
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_LABEL_DUPLICATE,
			bstr_get_line(file, 2), 3U, bstr_get_line(file, 2).str + 0, 5}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_LABEL_DUPLICATE,
			bstr_get_line(file, 3), 4U, bstr_get_line(file, 3).str + 0, 6}));
	ft_array_free(errors);

	file = str_to_bstr("label: live %:label\n"
						"live %:unknown\n");
	errors = get_errors(file);
	ASSERT(errors->len, ==, 3U);
	i = 0;
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_LABEL_UNKNOWN,
			bstr_get_line(file, 1), 2U, bstr_get_line(file, 1).str + 7, 7}));
	ft_array_free(errors);

	file = str_to_bstr("label: live %42\n"
						"label2: aff r1\n");
	errors = get_errors(file);
	ASSERT(errors->len, ==, 4U);
	i = 0;
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_WARNING, P_ERR_MSG_INS_LABEL_UNUSED,
			bstr_get_line(file, 0), 1U, bstr_get_line(file, 0).str + 0, 5}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_WARNING, P_ERR_MSG_INS_LABEL_UNUSED,
			bstr_get_line(file, 1), 2U, bstr_get_line(file, 1).str + 0, 6}));
	ft_array_free(errors);

	// Multiple errors test
	file = str_to_bstr(".name \"NAME\"\n"
					   ".code \"CODE\"\n"
					   "label: live r1\n"
					   "unknown\n"
					   "ld r1, r1, r1\n"
						"zjmp %:unknown\n"
						"label: aff %42\n");
	errors = get_errors(file);
	ASSERT(errors->len, ==, 10U);
	i = 0;
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_FORBID_REG_ARG,
			bstr_get_line(file, 2), 3U, bstr_get_line(file, 2).str + 12, 2}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_UNKNOWN,
			bstr_get_line(file, 3), 4U, bstr_get_line(file, 3).str + 0, 7}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_WRONG_OPERANDS_COUNT,
			bstr_get_line(file, 4), 5U, bstr_get_line(file, 4).str + 2, 11}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_FORBID_DIR_ARG,
			bstr_get_line(file, 6), 7U, bstr_get_line(file, 6).str + 11, 3}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_LABEL_DUPLICATE,
			bstr_get_line(file, 6), 7U, bstr_get_line(file, 6).str + 0, 5}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_ERROR, P_ERR_MSG_INS_LABEL_UNKNOWN,
			bstr_get_line(file, 5), 6U, bstr_get_line(file, 5).str + 7, 7}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_WARNING, P_ERR_MSG_INS_LABEL_UNUSED,
			bstr_get_line(file, 2), 3U, bstr_get_line(file, 2).str + 0, 5}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_WARNING, P_ERR_MSG_INS_LABEL_UNUSED,
			bstr_get_line(file, 6), 7U, bstr_get_line(file, 6).str + 0, 5}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_WARNING, P_ERR_MSG_META_DIRECTIVE_UNKNOWN,
			bstr_get_line(file, 1), 2U, bstr_get_line(file, 1).str + 1, 4}));
	ERROR_CMP(errors, i++,
		((t_parse_error){
			P_ERR_TYPE_WARNING, P_ERR_MSG_META_MISS_DIRECTIVE_COMMENT,
			bstr_get_line(file, 6), 7U, NULL, 0}));
	ft_array_free(errors);

	// No errors test
	file = str_to_bstr(".name \"NAME\"\n"
					   ".comment \"COMMENT\"\n"
					   "\n"
					   "label: live %2147483647\n"
						"zjmp %:label\n"
						"ld %-2147483648, r16\n"
						"add r1, r2, r3\n"
						"xor %:label-only, :label, r1\n"
						"aff r16\n"
						"label-only:");
	errors = get_errors(file);
	ASSERT(errors->len, ==, 0U);
	ft_array_free(errors);
}

t_array *get_instructions(char *file)
{
	t_array *txt_directives;
	t_array *instructions;

	txt_directives = file_to_txt_directives(str_to_bstr(file));
	instructions = txt_instructions_to_instructions(txt_directives);
	ft_array_free(txt_directives);
	return (instructions);
}

#define INS_CMP(instructions, index, ins) \
	do { \
		t_ins got = *(t_ins*)ft_array_get(instructions, index); \
		t_ins want = UNPACK(ins);							\
		ASSERT_OBJ(ins_equal, &got, &want, == true, ins_print); \
	} while (0)

void test_txt_instructions_to_instructions()
{
	t_array *instructions;
	size_t  i;

	// Simple test
	instructions = get_instructions(
		"live %42\n"
		"aff r16\n"
	);
	ASSERT(instructions->len, ==, 2U);
	i = 0;
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[0],
			.args_type = {DIR_ARG, NO_ARG, NO_ARG},
			.args = {0x2a, 0, 0},
			.size = 5,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[15],
			.args_type = {REG_ARG, NO_ARG, NO_ARG},
			.args = {0x10, 0, 0},
			.size = 3,
	}));
	ft_array_free(instructions);

	// Label references same instruction
	instructions = get_instructions(
		"label: live %:label\n"
	);
	ASSERT(instructions->len, ==, 1U);
	i = 0;
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[0],
			.args_type = {DIR_ARG, NO_ARG, NO_ARG},
			.args = {0x0, 0, 0},
			.size = 5,
	}));
	ft_array_free(instructions);

	// Label references instruction before
	instructions = get_instructions(
		"label: live %42\n"
		"lfork %:label\n"
		"lfork %:label\n"
	);
	ASSERT(instructions->len, ==, 3U);
	i = 0;
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[0],
			.args_type = {DIR_ARG, NO_ARG, NO_ARG},
			.args = {0x2a, 0, 0},
			.size = 5,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[14],
			.args_type = {DIR_ARG, NO_ARG, NO_ARG},
			.args = {0xfffffffb, 0, 0},
			.size = 3,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[14],
			.args_type = {DIR_ARG, NO_ARG, NO_ARG},
			.args = {0xfffffff8, 0, 0},
			.size = 3,
	}));
	ft_array_free(instructions);

	// Label references instruction after
	instructions = get_instructions(
		"lfork %:label\n"
		"lfork %:label\n"
		"label: live %42\n"
	);
	ASSERT(instructions->len, ==, 3U);
	i = 0;
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[14],
			.args_type = {DIR_ARG, NO_ARG, NO_ARG},
			.args = {0x06, 0, 0},
			.size = 3,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[14],
			.args_type = {DIR_ARG, NO_ARG, NO_ARG},
			.args = {0x03, 0, 0},
			.size = 3,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[0],
			.args_type = {DIR_ARG, NO_ARG, NO_ARG},
			.args = {0x2a, 0, 0},
			.size = 5,
	}));
	ft_array_free(instructions);

	// Multiple labels in the same instruction
	instructions = get_instructions(
		"label: live %42\n"
		"ldi :label, %:label, r1\n"
		"sti r1, :label, %:label\n"
		"ldi :label2, %:label2, r1\n"
		"sti r1, :label2, %:label2\n"
		"label2: live %42\n"
	);
	ASSERT(instructions->len, ==, 6U);
	i = 0;
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[0],
			.args_type = {DIR_ARG, NO_ARG, NO_ARG},
			.args = {0x2a, 0, 0},
			.size = 5,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[9],
			.args_type = {IND_ARG, DIR_ARG, REG_ARG},
			.args = {0xfffffffb, 0xfffffffb, 1},
			.size = 7,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[10],
			.args_type = {REG_ARG, IND_ARG, DIR_ARG},
			.args = {1, 0xfffffff4,  0xfffffff4},
			.size = 7,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[9],
			.args_type = {IND_ARG, DIR_ARG, REG_ARG},
			.args = {0x0e, 0x0e, 1},
			.size = 7,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[10],
			.args_type = {REG_ARG, IND_ARG, DIR_ARG},
			.args = {1, 0x07,  0x07},
			.size = 7,
	}));
	ft_array_free(instructions);

	// All the instructions
	instructions = get_instructions(
		"live %42\n"
		"ld %42, r1\n"
		"st r1, 42\n"
		"add r1, r2, r3\n"
		"sub r1, r2, r3\n"
		"and %42, 42, r16\n"
		"or %42, 42, r16\n"
		"xor %42, 42, r16\n"
		"zjmp %42\n"
		"ldi 42, %42, r1\n"
		"sti r1, 42, %42\n"
		"fork %42\n"
		"lld 42, r1\n"
		"lldi 42, %42, r1\n"
		"lfork %42\n"
		"aff r16\n"
	);
	ASSERT(instructions->len, ==, 16U);
	i = 0;
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[0],
			.args_type = {DIR_ARG, NO_ARG, NO_ARG},
			.args = {0x2a, 0, 0},
			.size = 5,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[1],
			.args_type = {DIR_ARG, REG_ARG, NO_ARG},
			.args = {0x2a, 1, 0},
			.size = 7,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[2],
			.args_type = {REG_ARG, IND_ARG, NO_ARG},
			.args = {1, 0x2a, 0},
			.size = 5,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[3],
			.args_type = {REG_ARG, REG_ARG, REG_ARG},
			.args = {1, 2, 3},
			.size = 5,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[4],
			.args_type = {REG_ARG, REG_ARG, REG_ARG},
			.args = {1, 2, 3},
			.size = 5,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[5],
			.args_type = {DIR_ARG, IND_ARG, REG_ARG},
			.args = {0x2a, 0x2a, 16},
			.size = 9,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[6],
			.args_type = {DIR_ARG, IND_ARG, REG_ARG},
			.args = {0x2a, 0x2a, 16},
			.size = 9,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[7],
			.args_type = {DIR_ARG, IND_ARG, REG_ARG},
			.args = {0x2a, 0x2a, 16},
			.size = 9,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[8],
			.args_type = {DIR_ARG, NO_ARG, NO_ARG},
			.args = {0x2a, 0, 0},
			.size = 3,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[9],
			.args_type = {IND_ARG, DIR_ARG, REG_ARG},
			.args = {0x2a, 0x2a, 1},
			.size = 7,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[10],
			.args_type = {REG_ARG, IND_ARG, DIR_ARG},
			.args = {1, 0x2a, 0x2a},
			.size = 7,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[11],
			.args_type = {DIR_ARG, NO_ARG, NO_ARG},
			.args = {0x2a, 0, 0},
			.size = 3,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[12],
			.args_type = {IND_ARG, REG_ARG, NO_ARG},
			.args = {0x2a, 1, 0},
			.size = 5,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[13],
			.args_type = {IND_ARG, DIR_ARG, REG_ARG},
			.args = {0x2a, 0x2a, 1},
			.size = 7,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[14],
			.args_type = {DIR_ARG, NO_ARG, NO_ARG},
			.args = {0x2a, 0, 0},
			.size = 3,
	}));
	INS_CMP(instructions, i++,
		((t_ins){
			.instruction = &g_instructions[15],
			.args_type = {REG_ARG, NO_ARG, NO_ARG},
			.args = {16, 0, 0},
			.size = 3,
	}));
	ft_array_free(instructions);
}

int main()
{
	RUN_TEST(test_file_to_txt_directives);
	RUN_TEST(test_line_to_txt_directive);

	RUN_TEST(test_ins_set_size);
	RUN_TEST(test_ins_set_args_type);
	RUN_TEST(test_ins_args_ok);
	RUN_TEST(test_bin_to_ins);
	RUN_TEST(test_txt_to_txt_meta);
	RUN_TEST(test_txt_to_txt_ins);
	RUN_TEST(test_txt_ins_to_ins);
	RUN_TEST(test_ins_to_bin_ins);
	RUN_TEST(test_ins_to_str);
	RUN_TEST(test_get_prog_header);

	RUN_TEST(test_txt_ins_get_ins_spec);

	RUN_TEST(test_check_syntax_file);
	RUN_TEST(test_check_semantic_txt_directives);

	RUN_TEST(test_txt_instructions_to_instructions);
}
