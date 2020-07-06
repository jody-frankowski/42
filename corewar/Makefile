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

.PHONY: all assembler libft vm

all: libft assembler vm

assembler:
	make -C assembler/

libft:
	make -C libft/

vm:
	make -C vm/

clean:
	make -C assembler/ clean
	make -C libft/ clean
	make -C vm/ clean

fclean:
	make -C assembler/ fclean
	make -C libft/ fclean
	make -C vm/ fclean

re:
	make -C assembler/ re
	make -C libft/ re
	make -C vm/ re
