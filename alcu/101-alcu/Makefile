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

NAME = alum1
BUILD_DIR = build
SRC = build.c helpers.c main.c matches_to_remove.c print.c
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(BUILD_DIR)/,$(OBJ))
DEPS = $(OBJS:.o=.d)
INCLUDES = -I libft/
LDFLAGS = -L libft/
LDLIBS = -lft
EXT_DEPS = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(EXT_DEPS)
	@# LDFLAGS need to appear after OBJS https://eli.thegreenplace.net/2013/07/09/library-order-in-static-linking
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)

-include $(DEPS)

$(OBJS): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@# $(BUILD_DIR) isn\'t a dependency of this target because it always updates
	@# ^^^ http://www.gnu.org/software/make/manual/make.html#index-_0024_0028_0040D_0029
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJS) $(DEPS)
	[ -d $(BUILD_DIR) ] && rmdir $(BUILD_DIR) || true

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

norm:
	norminette $(SRC) $(HEADERS)

libft/libft.a:
	make -C libft

memcheck: test
	valgrind --show-leak-kinds=all --leak-check=full --track-origins=yes tests/test

# Make Debug Helper
print-% :
	@echo $* = $($*)
