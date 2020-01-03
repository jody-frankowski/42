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
BUILD_DIR = build
SRC = ft_atoi.c ft_bstrdup.c ft_bstrtrunc.c ft_charcasecmp.c ft_incharset.c ft_isalpha.c ft_isdigit.c ft_islower.c ft_isupper.c ft_lstfree.c ft_lstnew.c ft_lstpush.c ft_max.c ft_memchr.c ft_memcpy.c ft_memdel.c ft_min.c ft_num_digits.c ft_pow.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_realloc.c ft_stpncpy.c ft_strcasecmp.c ft_strcat.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncasecmp.c ft_strncmp.c ft_strndup.c ft_strnlen.c ft_strspn.c ft_strtol.c get_next_line.c
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(BUILD_DIR)/,$(OBJ))
DEPS = $(OBJS:.o=.d)
HEADERS = libft.h

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $?
	ranlib $(NAME)

-include $(DEPS)

$(OBJS): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@# $(BUILD_DIR) isn\'t a dependency of this target because it always updates
	@# ^^^ http://www.gnu.org/software/make/manual/make.html#index-_0024_0028_0040D_0029
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette $(SRC) $(HEADERS)

debug: $(NAME)
	make -C tests
	lldb tests/test

test: $(NAME)
	make -C tests
	tests/test

memcheck: test
	valgrind --show-leak-kinds=all --leak-check=full --track-origins=yes tests/test

# Make Debug Helper
print-% :
	@echo $* = $($*)
