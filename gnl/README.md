# `get\_next\_line` (gnl) - A Function to Read a File Line by Line

Subject: [get\_next\_line.en.pdf](get\_next\_line.en.pdf)

The goal of this project was to write a function that will read a single line
from a file descriptor. This is the equivalent of
[getline(3)](https://linux.die.net/man/3/getline).

## Setup

Build:

```
make -C libft
gcc -I libft/includes get_next_line.c -c -o get_next_line.o
```

## Usage

```c
int get_next_line(const int fd, char **line);
```
