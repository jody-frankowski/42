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
.PHONY = all clean fclean norm re

CC = gcc
COMPILER = $(shell gcc -v 2>&1 | grep 'Apple LLVM' > /dev/null && echo "clang" || echo "gcc")
UNAME := $(shell uname)

### CFLAGS
CFLAGS  = -Wall -Wextra -Werror -Werror=vla
CFLAGS += -Werror=format=2
CFLAGS += -Werror=null-dereference
CFLAGS += -Werror=shadow
CFLAGS += -pipe -std=gnu99 -march=native

ifeq ("$(COMPILER)", "gcc")
  CFLAGS += -Werror=duplicated-branches
  CFLAGS += -Werror=duplicated-cond
  CFLAGS += -Werror=logical-op
endif

ifeq ($(DEBUG), 1)
  CFLAGS += -g -fno-omit-frame-pointer
ifeq ("$(COMPILER)", "clang")
  CFLAGS += -fsanitize=undefined -fsanitize=address
endif
endif
### CFLAGS

### LIBRARIES
DEPENDENCIES = libft libtest
# We assume all our dependencies have a include/ that we want to include
INCLUDES = $(foreach lib,$(DEPENDENCIES),-I lib/$(lib)/include/) -I include/
LDFLAGS  = $(foreach lib,$(DEPENDENCIES),-L lib/$(lib)/)
LDLIBS   = $(foreach lib,$(DEPENDENCIES),-l$(lib:lib%=%))
ifeq ($(UNAME), Linux)
	CFLAGS += `pkg-config --cflags libbsd-overlay`
	LDLIBS += `pkg-config --libs libbsd-overlay`
endif
### LIBRARIES

NAME      = test
BUILD_DIR = build
SRC_DIR   = src
SRCS      = $(wildcard $(SRC_DIR)/*.c)
OBJS      = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(DEPENDENCIES) $(OBJS)
# Tests wether NAME ends with ".a"
ifeq ($(patsubst %.a,,$(NAME)),)
	ar ruc $(NAME) $(OBJS)
	ranlib $(NAME)
else
	@# LDLIBS needs to appear after OBJS https://eli.thegreenplace.net/2013/07/09/library-order-in-static-linking
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
endif

$(DEPENDENCIES):
	make -C lib/$@

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@# $(BUILD_DIR) isn\'t a dependency of this target because it always updates
	@# ^^^ http://www.gnu.org/software/make/manual/make.html#index-_0024_0028_0040D_0029
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# "Dependency files" (*.d) are produced by $(CC) -MMD -MP and contain Makefile
# rules that make object files dependent on the headers they include. This makes
# subsequent Makefile runs faster if a header is changed by only recompiling the
# source files that include these headers.
HEADER_DEPS = $(OBJS:.o=.d)
-include $(HEADER_DEPS)

clean:
	rm -f $(OBJS) $(HEADER_DEPS)
	[ -d $(BUILD_DIR) ] && rmdir $(BUILD_DIR) || true

fclean: clean
	rm -f $(NAME)

norm:
	norminette include/ src/

# Make Debug Helper
print-% :
	@echo $* = $($*)

re: fclean all

.PHONY: $(PHONY)
