# bsq - Find the Biggest Square on a Map

Subject: [bsq.en.pdf](bsq.en.pdf)

The goal of this project was to find the biggest square that could fit on a map
with obstacles, as fast as possible.

Please note that a lot of the code may be unreadable because of The Norm
restrictions.

## Rules

You must find the biggest square, that doesn't cover any obstacle and the first
one starting from the top left if there are multiple ones of the same size.

For the following map (the first line indicates the number of lines, the empty
symbol, the obstacle symbol and the square symbol, in this order):

```
10.ox
..........
..........
..........
oo......o.
.o........
.o........
..o.......
.o....o...
o.........
o........o
```

The result of the program execution (`./bsq map`) should be:

```
..xxxxxx..
..xxxxxx..
..xxxxxx..
ooxxxxxxo.
.oxxxxxx..
.oxxxxxx..
..o.......
.o....o...
o.........
o........o
```

## Algorithm

Our bsq used the following algorithm:

- Consider the map to be a grid of zeroes
- Start from the top left corner
- Move from left to right, top to bottom
- For the current tile add one to the minimum value between the tile directly
  above, the one directly to the left and the one directly above and to the
  left. The default value for tiles outside the map or ones that contain an
  obstacle are 0.
- The tile with the biggest number will contain the side length of the biggest
  square and will be the bottom right corner of this square

Example (with the map above):

```
1111111111
1222222222
1233333333
oo123444o1
1o12345511
1o12345622
11o1234533
1o1123o123
o112231123
o12233222o
```

As you can see, we have a 6 in the same tile as the bottom right corner of the
square from example above.

## Setup

```sh
make
```

## Usage

```
$ ./bsq MAPFILE
```
