# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfrankow <jfrankow@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 1970/01/01 00:00:00 by jfrankow          #+#    #+#              #
#    Updated: 1970/01/01 00:00:00 by jfrankow         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

DEPENDENCIES = libtest libunit libft
LIBNAME      =
NAME         = test

include common.mk

ifeq ($(shell uname), Linux)
  CFLAGS += `pkg-config --cflags libbsd-overlay`
  LDLIBS += `pkg-config --libs libbsd-overlay`
endif
