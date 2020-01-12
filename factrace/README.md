# FactRace - A Prime Factorization Race

Subject: [factrace.pdf](factrace.pdf)

This project had to be done in 48 hours and the goal was to be the one to
factorize the "biggest" (the furthest in an unknown list) primes. We were given
example files that were meant to resemble the ones used to evaluate us. This
allowed us to make some "predictions" about what you could try to factorize and
what wasn't worth it.

We got 1st place 🥇!

We used [Pollard's Rho
Algorithm](https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm) to
factorize the numbers ([fact.c](src/fact.c)).

A trick I used was to try to factorize the last line that was 3 digits longer
than its immediate neighbors ([main.c](src/main.c#L38)).

I had gathered a lot of informations on the examples files, such as:
- The time to factorize with a dumb algorithm, our algorithm or the with the
  fastest program we could find
- The length of the factors (if both had the same size, or if one of them was
  more trivial)
- ...

With these informations it was evident that in some of the example files the
lines that were 3 digits longer than their immediate neighbors were factorizable
in a realistic time, while their neighbors didn't seem to be (even with the
fastest algo/program we could find). (We didn't get any metrics on how well the
teams had done, so it isn't possible to definitively conclude that this gave us
the edge).

Please keep in mind that this project was done in a group, so obviously part of
the code or ideas may not be not mine.

## Setup

The project depends on [GMP](https://gmplib.org/), but you don't need to
download and install it. For the evaluation, we shipped a compiled for macOS
`.a` file and now I have replaced this file with an automated download and
compilation task in the Makefile. It pulls the exact same version, and compiles
it with the exact same options.

Build:

```sh
$ make
```

## Usage

Run on a single file:

```
$ cat resources/test03.ftr | ./factrace
25110725352025042209755017429017573478877423902250842639000863=3*8370241784008347403251672476339191159625807967416947546333621
```

Run with the `factmouli` binary (runs only on macOS):

```
$ ./factmouli ./factrace resources/test02.ftr
Running tests...
==> testing with 20000 ms
Control ok.
Position in test file is 13
==> testing with 12000 ms
Control ok.
Position in test file is 13
==> testing with 8000 ms
Control ok.
Position in test file is 13
==> testing with 3000 ms
Control ok.
Position in test file is 13
==> testing with 700 ms
Control ok.
Position in test file is 13
```
