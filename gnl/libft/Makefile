#******************************************************************************#
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: jfrankow <jfrankow@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/07/16 09:55:43 by jfrankow     #+#   ##    ##    #+#        #
#    Updated: 2018/07/16 09:55:44 by jfrankow    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
#******************************************************************************#

.PHONY: all clean debug fclean norm test memcheck re

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Werror=vla \
-Werror=double-promotion \
-Werror=null-dereference \
-Werror=shadow \
-Werror=format-security \
-pipe -std=gnu99 -march=native
ifeq ($(DEBUG), 1)
  CFLAGS += -g -fno-omit-frame-pointer
endif

NAME = libft.a
# No trailing slashes!!
BUILD_DIR = build
SRC = ft_bstrdup.c ft_bstrtrunc.c ft_lstfree.c ft_lstnew.c ft_lstpush.c ft_memchr.c ft_memcpy.c ft_reallocf.c
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(BUILD_DIR)/,$(OBJ))
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $?
	ranlib $(NAME)

-include $(DEPS)

$(OBJS): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@# $(BUILD_DIR) isn\'t a dependency of this target because it always updates
	@# ^^^ http://www.gnu.org/software/make/manual/make.html#index-_0024_0028_0040D_0029
	$(CC) $(CFLAGS) -I includes/ -MMD -MP -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all
