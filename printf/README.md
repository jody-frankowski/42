# `ft_printf`

Subject: [ft_printf.en.pdf](ft_printf.en.pdf)

This is a simple implementation of some of the printf features.

The following features are supported:

- Flags:
  - `#`
  - `0`
  - `-`
  - `<space>`
  - `+`
- Field Width
- Precision
- Length Modifiers:
  - `hh`
  - `h`
  - `l`
  - `ll`
  - `L`
- Conversion Specifiers:
  - `d` `i`
  - `o`
  - `u`
  - `x` `X`
  - `f` `F` (only some simple conversions)
  - `c`
  - `s`
  - `p`
  - `%`

The test suite uses my [libunit test framework](../libunit) and can be found in
[test/src/tests.c](test/src/tests.c).
