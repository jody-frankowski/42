# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/07/16 09:55:43 by jfrankow     #+#   ##    ##    #+#        #
#    Updated: 2018/07/25 22:51:17 by tiperoul    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = bsq

.PHONY = all clean fclean norm test memcheck re

CC = gcc
INCLUDES = -I includes/
# CFLAGS = -Wall -Wextra -Werror -O 2
CFLAGS = -Wall -Wextra -Werror -O2

# No trailing slashes!!
SRCS_DIR = srcs
OBJS_DIR = objs
SRC = $(NAME).c \
		coord.c \
		ft_atoi.c \
		ft_memcpy.c \
		ft_min.c \
		ft_putchar.c \
		ft_putnbr.c \
		ft_putstr.c \
		ft_realloc.c \
		ft_strcat.c \
		ft_strlen.c \
		ft_strdup.c \
		grid.c \
		spec.c \
		treat.c
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJS_DIR)/,$(OBJ))
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

-include $(DEPS)

$(OBJS): $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	@# $(OBJS_DIR) isn\'t a dependency of this target because it always update
	@# ^^^ http://www.gnu.org/software/make/manual/make.html#index-_0024_0028_0040D_0029
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette srcs/ includes/
	make -C tests norm

test:
	make -C tests
	script/test

memcheck: all
	valgrind -v --show-leak-kinds=all --leak-check=full --track-origins=yes \
	./$(NAME)

# debugging make
print-% :
	@echo $* = $($*)
