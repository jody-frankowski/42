# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/07/16 09:55:43 by jfrankow     #+#   ##    ##    #+#        #
#    Updated: 2018/07/16 09:55:44 by jfrankow    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY = all clean fclean memcheck re

CC = gcc
INCLUDES = -I includes/
CFLAGS = -Wall -Wextra -Werror

NAME = ft_advanced_do-op
# No trailing slashes!!
SRCS_DIR = srcs
OBJS_DIR = objs
SRC = ft_advanced_do_op.c ft_atoi.c ft_math.c ft_putchar.c ft_putnbr.c ft_putstr.c ft_strcmp.c
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

memcheck: all
	valgrind -v --show-leak-kinds=all --leak-check=full --track-origins=yes \
	./$(NAME)

# debugging make
print-% :
	@echo $* = $($*)
