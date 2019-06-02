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

### CFLAGS
CFLAGS  = -Wall -Wextra -Werror -Werror=vla -Wno-missing-braces -Wno-missing-field-initializers
CFLAGS += -O3 -march=native -pipe

### CFLAGS

### LIBRARIES
INCLUDES = -I include/
LDFLAGS  = -L lib/ -Wl,-no_pie
LDLIBS   = -lgmp
### LIBRARIES

NAME      = factrace
BUILD_DIR = build
SRC_DIR   = src
SRCS      = $(wildcard $(SRC_DIR)/*.c)
OBJS      = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(DEPENDENCIES) $(OBJS)
	@# LDLIBS needs to appear after OBJS https://eli.thegreenplace.net/2013/07/09/library-order-in-static-linking
	gcc $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)

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

clean:
	rm -f $(OBJS) $(HEADER_DEPS)
	[ -d $(BUILD_DIR) ] && rmdir $(BUILD_DIR) || true

fclean: clean
	rm -f $(NAME)

norm:
	norminette include/ src/

re: fclean all

.PHONY: $(PHONY)
