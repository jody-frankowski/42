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

COMPILER = $(shell gcc -v 2>&1 | grep 'Apple LLVM' > /dev/null && echo "clang" || echo "gcc")

### CFLAGS
CFLAGS  = -Wall -Wextra -Werror -Werror=vla
CFLAGS += -O3 -march=native -pipe
### CFLAGS

### LIBRARIES
INCLUDES = -I include/
ifeq ("$(COMPILER)", "gcc")
LDFLAGS  = -L lib/
else
LDFLAGS  = -L lib/ -Wl,-no_pie
endif
LDLIBS   = -lgmp
### LIBRARIES

NAME      = factrace
BUILD_DIR = build
SRC_DIR   = src
SRCS      = $(wildcard $(SRC_DIR)/*.c)
OBJS      = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): lib/libgmp.a $(OBJS)
	@# LDLIBS needs to appear after OBJS https://eli.thegreenplace.net/2013/07/09/library-order-in-static-linking
ifeq ("$(COMPILER)", "gcc")
	gcc $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -no-pie -o $(NAME)
else
	gcc $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
endif

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@# $(BUILD_DIR) isn\'t a dependency of this target because it always updates
	@# ^^^ http://www.gnu.org/software/make/manual/make.html#index-_0024_0028_0040D_0029
	gcc $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# "Dependency files" (*.d) are produced by $(CC) -MMD -MP and contain Makefile
# rules that make object files dependent on the headers they include. This makes
# subsequent Makefile runs faster if a header is changed by only recompiling the
# source files that include these headers.
HEADER_DEPS = $(OBJS:.o=.d)
-include $(HEADER_DEPS)

lib/libgmp.a:
	@mkdir -p lib
	cd lib/ && \
	curl -L -O https://web.archive.org/web/20200106141404/https://ftp.gnu.org/gnu/gmp/gmp-6.1.2.tar.xz && \
	tar xJvf gmp-6.1.2.tar.xz && \
	cd gmp-6.1.2 && \
	CFLAGS="-O3 -pedantic -fomit-frame-pointer -m64 -march=native" ./configure && \
	make && \
	mv .libs/libgmp.a ../

clean:
	rm -f $(OBJS) $(HEADER_DEPS)
	[ -d $(BUILD_DIR) ] && rmdir $(BUILD_DIR) 2>/dev/null || true
	rm -f  lib/gmp-6.1.2.tar.xz
	rm -rf lib/gmp-6.1.2/
	rm -f  lib/libgmp.a

fclean: clean
	rm -f $(NAME)

norm:
	norminette include/ src/

re: fclean all

.PHONY: $(PHONY)
