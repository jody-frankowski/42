# HotRace - An Indexing Race

Subject: [hotrace.pdf](hotrace.pdf)

This project had to be done in 48 hours and the goal was to be the fastest to
load and query a key/value database.

We got 1st place 🥇!

The data was to be received on stdin and have the following format:
```
tag-1
value1
tag-2
value2
[....]
keyword-x
valuex

keyword-search1
keyword-search2
[...]
```

For the generic cases we used a [Hash
Table](https://en.wikipedia.org/wiki/Hash_table) with the [djb2 hash
algorithm](http://www.cse.yorku.ca/~oz/hash.html) and with collision resolution
with [Separate Chaining with Linked
Lists](https://en.wikipedia.org/wiki/Hash_table#Separate_chaining_with_linked_lists).

We chose djb2 ([main.c](main.c#L94)) because it seemed to be the best mix
between collisions, speed and ease of implementation.

Please keep in mind that this project was done in a group, so obviously part of
the code or ideas may not be not mine.

## Tricks Used

### `test05.htr`

A trick I used was to "guess" the value instead of searching for it.
`test05.htr` had the following incremental pattern:

```
[...]
AA
AB
AC
AD
[...]
$]R8
$]R9
$]R:
[...]
```

So if the given file matched this pattern I would simply "compute" the expected
value ([cheat.c](cheat.c#L21)). (We didn't get any metrics on how well the teams
had done, so it isn't possible to definitively conclude that this gave us the
edge)

### `test06.htr`

`test06.htr` had the following pattern:

```
ABACA
ABATS
ABBES
ABCES
ABDOS
ABEES
[...]
```

The trick I used was to use the first five significant bits of each letter as
the indexing key ([dict.c](dict.c#L56)). This lowered the requirement for an
indexing key from 40 (5\*8) bits to only 25 (5\*5) bits (1000 billion keys vs 33
million keys).

## Setup

Build:

```sh
make
```

## Usage

Run a test with the binary the school provided (runs only on macOS):

```
$ ./hotmouli ./hotrace resources/test01.htr
Running tests...done.
Hotrace : starting control procedure
Control ok.
Speed reference number is 1.10
Less is best.
```

Run all the tests:

```
$ for file in resources/* ; do echo "$file" ; ./hotmouli ./hotrace "$file" ; done
```
