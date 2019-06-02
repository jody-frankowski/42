# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/07/16 09:55:43 by jfrankow     #+#   ##    ##    #+#        #
#    Updated: 2018/07/23 11:20:21 by tiperoul    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = test

.PHONY = all clean fclean norm memcheck re

CC = gcc
INCLUDES = -I includes/ -I ../includes
# CFLAGS = -Wall -Wextra -Werror -O 2
CFLAGS = -Wall -Wextra -Werror

# No trailing slashes!!
SRCS_DIR = srcs
OBJS_DIR = objs
EOBJS_DIR = ../objs

SRC = $(NAME).c ft_memcmp.c ft_putnbr.c ft_strcmp.c tests.c
ESRC = ft_atoi.c \
		ft_memcpy.c \
		ft_putchar.c \
		ft_putnbr.c \
		ft_putstr.c \
		ft_strlen.c \
		ft_strdup.c \
		ft_realloc.c \
		grid.c
EOBJ = $(ESRC:.c=.o)
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJS_DIR)/,$(OBJ))
EOBJS = $(addprefix $(OBJS_DIR)/,$(EOBJ))
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS) $(addprefix $(EOBJS_DIR)/,$(EOBJ))
	$(CC) $(CFLAGS) $^ -o $(NAME)

-include $(DEPS)

$(OBJS): $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	@# $(OBJS_DIR) isn\'t a dependency of this target because it always update
	@# ^^^ http://www.gnu.org/software/make/manual/make.html#index-_0024_0028_0040D_0029
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# $(EOBJS):
$(addprefix $(EOBJS_DIR)/,$(EOBJ)):
	make -C .. $(EOBJS)

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette srcs/ includes/

memcheck: all
	valgrind -v --show-leak-kinds=all --leak-check=full --track-origins=yes \
	./$(NAME)

# debugging make
print-% :
	@echo $* = $($*)
