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

# The real PHONY target is set at the end of the Makefile
.PHONY = all clean fclean re

CC = gcc
COMPILER = gcc
UNAME := $(shell uname)

### CFLAGS
CFLAGS  = -Wall -Wextra -Werror -Werror=vla
### CFLAGS


NAME      = fillit
BUILD_DIR = build
SRCS      = ft_memcpy.c  ft_memmove.c  ft_putchar_fd.c  ft_putstr.c  ft_putstr_fd.c  ft_read_up_to.c  main.c  parse.c  parse2.c  print.c  solve.c  solve17.c  utils.c
OBJS      = $(SRCS:%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(DEPENDENCIES) $(OBJS)
	@# LDLIBS needs to appear after OBJS https://eli.thegreenplace.net/2013/07/09/library-order-in-static-linking
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)

$(DEPENDENCIES):
	make -C lib/$@

$(OBJS): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@# $(BUILD_DIR) isn\'t a dependency of this target because it always updates
	@# ^^^ http://www.gnu.org/software/make/manual/make.html#index-_0024_0028_0040D_0029
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# "Dependency files" (*.d) are produced by $(CC) -MMD -MP and contain Makefile
# rules that make object files dependent on the headers they include. This makes
# subsequent Makefile runs faster if a header is changed by only recompiling the
# source files that include these headers.
HEADER_DEPS = $(OBJS:.o=.d)
-include $(HEADER_DEPS)

clean:
	rm -f $(OBJS) $(HEADER_DEPS)
	[ -d $(BUILD_DIR) ] && rmdir $(BUILD_DIR) 2>/dev/null || true

fclean: clean
	rm -f $(NAME)

# Make Debug Helper
print-% :
	@echo $* = $($*)

re: fclean all

.PHONY: $(PHONY)
