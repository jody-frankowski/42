# Fillit - Fit Tetriminos In The Smallest Square Possible As Fast As Possible

Subject: [fillit.en.pdf](fillit.en.pdf)

The goal of this project was to find an algorithm (if possible the fastest) that
can fit tetriminos in the smallest square possible.

## Setup

Build:

```
make
```

## Usage

Solve for a file:

```
$ cat sample
....
##..
.#..
.#..

....
####
....
....

#...
###.
....
....

....
##..
.##.
....
$ ./fillit sample
DDAA
CDDA
CCCA
BBBB
```
