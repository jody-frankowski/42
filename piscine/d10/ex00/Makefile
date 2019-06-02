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

.PHONY = all clean fclean re

CC = gcc
INCLUDES = -I includes/
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a
# No trailing slashes!!
SRCS_DIR = srcs
OBJS_DIR = objs
SRC = ft_putchar.c ft_putstr.c ft_strcmp.c ft_strlen.c ft_swap.c
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJS_DIR)/,$(OBJ))
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	ar ruc $(NAME) $?
	ranlib $(NAME)

-include $(DEPS)

# %.o: srcs/%.c
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
