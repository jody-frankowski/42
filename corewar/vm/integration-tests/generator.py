#!/usr/bin/env python3

import os

COREWAR_MAGIC = bytearray.fromhex("00ea83f3")

def header(
		magic: bytearray,
		name: bytearray,
		size: bytearray,
		comment: bytearray
	) -> bytearray:
	"""
	Construct a bytearray that represents a corewar binary header.
	"""

	header = bytearray()

	header.extend(magic)
	header.extend(name)
	header.extend(size)
	header.extend(comment)
	# Does not need to be zero (see generate_non_null_header_padding_bytes)
	header.extend(bytes(b'\x00\x00\x00\x00'))

	return header


def name(name: str) -> bytearray:
	"""
	Transform a string to a bytearray, and fill it up to the required size of a
	name field in a corewar binary header.
	"""

	name = bytearray(name, 'utf-8')
	if len(name) < 128:
		name.extend(b'N' * 128)
	name = name[0:128]

	return name


def comment(comment: str) -> bytearray:
	"""
	Transform a string to a bytearray, and fill it up to the required size of a
	comment field in a corewar binary header.
	"""

	comment = bytearray(comment, 'utf-8')
	if len(comment) < 2048:
		comment.extend(b'C' * 2048)
	comment = comment[0:2048]

	return comment


def size(size: int) -> bytes:
	"""
	Transform an integer to a bytearray of the required size of the program size
	field in a corewar binary header.
	"""

	return size.to_bytes(8, 'big')


def write_file(filename: str, data: bytearray):
	"""
	Write data to a file.
	"""

	os.makedirs(os.path.dirname(filename), exist_ok=True)
	file = open(filename, "wb")
	file.write(data)


# Errors
def generate_program_size_not_equal_to_real_size(test_name: str):
	output = header(
		COREWAR_MAGIC,
		name("NAME"),
		size(3),
		comment("COMMENT")
	)

	write_file(test_name, output)


# Not Errors
def generate_program_size_equals_zero(test_name: str):
	output = header(
		COREWAR_MAGIC,
		name("NAME"),
		size(0),
		comment("COMMENT")
	)

	write_file(test_name, output)


def generate_non_zero_acb(test_name: str):
	output = header(
		COREWAR_MAGIC,
		name("NAME"),
		size(3),
		comment("COMMENT")
	)

	# aff r1
	# Should be 10 40 01
	# Web put 10 7f 01 instead
	output.extend(bytes([0x10, 0b01111111, 0x01]))

	write_file(test_name, output)


def generate_null_byte_in_comment(test_name: str):
	output = header(
		COREWAR_MAGIC,
		name("NAME"),
		size(0),
		b'\x41\x00' * 1024
	)

	write_file(test_name, output)


def generate_null_byte_in_name(test_name: str):
	output = header(
		COREWAR_MAGIC,
		b'\x41\x00' * 64,
		size(0),
		comment("COMMENT"),
	)

	write_file(test_name, output)


def generate_non_null_header_padding_bytes(test_name: str):
	output = header(
		COREWAR_MAGIC,
		name("NAME"),
		size(0),
		comment("COMMENT"),
	)
	output = output[:-4]
	output.extend(b'\xff\xff\xff\xff')

	write_file(test_name, output)


if __name__ == "__main__":
	# Errors
	generate_program_size_not_equal_to_real_size(
		"errors/program_size_not_equal_to_real_size.cor"
	)

	# Not Errors
	generate_program_size_equals_zero(
		"not-errors/program_size_equals_zero.cor"
	)
	generate_non_zero_acb(
		"not-errors/non_zero_acb.cor"
	)
	generate_null_byte_in_comment(
		"not-errors/null_byte_in_comment.cor"
	)
	generate_null_byte_in_name(
		"not-errors/null_byte_in_name.cor"
	)
	generate_non_null_header_padding_bytes(
		"not-errors/non_null_header_padding_bytes.cor"
	)
