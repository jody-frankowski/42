CC = gcc
CFLAGS += -Wall -Wextra -Werror
SRC = dict.c ft_memcpy.c ft_strcmp.c main.c print.c read.c tab.c cheat.c
OBJ = $(SRC:.c=.o)
RM = rm -f

NAME = hotrace

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
