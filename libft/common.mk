# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    common.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#              #
#    Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# If you want to use this Makefile, in your Makefile you need to:
# - Set NAME to the name of the resulting binary that you want
# - Set LIBNAME to the name of the resulting static library that you want (Set
#   this if you want to do unit tests with the common test/ architecture).
# - Add a symlink in lib/ to the libraries on which your project depends
# - Set DEPENDENCIES to the libraries names in lib/.
#   Take care of the order in which they appear. If libb depends on liba then
#   DEPENDENCIES should be equal to "libb liba". (See LIBRARY comment below).

# All the variables can be overriden on the command line like so:
# make VAR=...
# Or overridden or appended in the Makefile that includes this file like so:
# VAR = ...
# or
# VAR += ...
# - Include this file with "include common.mk"

CC = clang

# Enable this to build with debug infos
DEBUG = 0
DEPS_TOO = 0

### CFLAGS
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -Werror=format=2
CFLAGS += -Werror=null-dereference
CFLAGS += -Werror=shadow
CFLAGS += -Werror=vla
CFLAGS += -pipe -std=gnu99 -march=native

ifeq ($(CC), gcc)
  CFLAGS += -Werror=duplicated-branches
  CFLAGS += -Werror=duplicated-cond
  CFLAGS += -Werror=logical-op
endif

ifeq ($(DEBUG), 1)
  CFLAGS += -g -fno-omit-frame-pointer
endif
### CFLAGS

### LIBRARIES
# For all the dependencies we assume that:
# - They are named libNAME
# - They are under lib/ as lib/libNAME
# - lib/libNAME/include contains its header files
# - The archive file is lib/libNAME/libNAME.a
INCLUDES = $(foreach lib,$(DEPENDENCIES),-I lib/$(lib)/include/) -I include/
LDFLAGS  = $(foreach lib,$(DEPENDENCIES),-L lib/$(lib)/)
LDLIBS   = $(foreach lib,$(DEPENDENCIES),-l$(lib:lib%=%))
DEPENDENCIES_LIB_FILES := $(foreach D,$(DEPENDENCIES),lib/$D/$D.a)
### LIBRARIES

BUILD_DIR = build
SRC_DIR   = src
SRCS      = $(wildcard $(SRC_DIR)/*.c)
OBJS      = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

PHONY += all
all: $(NAME) $(LIBNAME)

ifdef NAME
$(NAME): $(DEPENDENCIES_LIB_FILES) $(OBJS)
	@# LDLIBS needs to appear after OBJS https://eli.thegreenplace.net/2013/07/09/library-order-in-static-linking
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@
endif

ifdef LIBNAME
$(LIBNAME): $(DEPENDENCIES_LIB_FILES) $(OBJS)
	ar rc $@ $(OBJS)
	ranlib $@
endif

$(DEPENDENCIES_LIB_FILES): FORCE
	make -C $(dir $@)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# "Dependency files" (*.d) are produced by $(CC) -MMD -MP and contain Makefile
# rules that make object files dependent on the headers they include. This makes
# subsequent Makefile runs faster if a header is changed by only recompiling the
# source files that include these headers.
HEADER_DEPS = $(OBJS:.o=.d)
-include $(HEADER_DEPS)

PHONY += clean
clean:
	rm -f $(OBJS) $(HEADER_DEPS)
	[ -d $(BUILD_DIR) ] && rmdir $(BUILD_DIR) 2>/dev/null || true

PHONY += fclean
fclean: clean
ifdef LIBNAME
	rm -f $(LIBNAME)
endif
ifdef NAME
	rm -f $(NAME)
endif

PHONY += re
re: fclean all

PHONY += tests
tests:
	make -C test/

PHONY += FORCE
FORCE:

# Make Debug Helper
print-% :
	@echo $* = $($*)

.PHONY: $(PHONY)
