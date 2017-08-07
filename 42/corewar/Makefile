# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saubenne <saubenne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/23 15:41:46 by saubenne          #+#    #+#              #
#    Updated: 2017/07/27 15:36:36 by bmickael         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft
COREWAR = corewar
MSA = msa
ASM = asm

.PHONY: all clean fclean re libft

# Main compilation rule

all:
	make -C libft DEBUG=$(DEBUG)
	make -f Makefile_corewar DEBUG=$(DEBUG)
	make -f Makefile_asm DEBUG=$(DEBUG)
	make -f Makefile_msa DEBUG=$(DEBUG)	

# Single target Experiment

$(LIBFT):
	make -C libft DEBUG=$(DEBUG)

$(COREWAR):
	make -C libft DEBUG=$(DEBUG)
	make -f Makefile_corewar DEBUG=$(DEBUG)

$(ASM):
	make -C libft DEBUG=$(DEBUG)
	make -f Makefile_asm DEBUG=$(DEBUG)

$(MSA):
	make -C libft DEBUG=$(DEBUG)
	make -f Makefile_msa DEBUG=$(DEBUG)

# Common rules

clean:
	make -C libft clean
	make -f Makefile_corewar clean
	make -f Makefile_asm clean
	make -f Makefile_msa clean

fclean:
	make -C libft fclean
	make -f Makefile_corewar fclean
	make -f Makefile_asm fclean
	make -f Makefile_msa fclean

re: fclean all
