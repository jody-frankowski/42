#!/bin/sh

cd "$(dirname $0)"

gcc -c ft_*.c
ar rc libft.a ft_*.o
ranlib libft.a
