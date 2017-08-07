#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saubenne <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/23 15:41:46 by saubenne          #+#    #+#              #
#    Updated: 2017/05/09 18:46:17 by saubenne         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = push_swap checker generator
CC = gcc
PUSH_SWAP_HEADER = push_swap.h
CHECKER_HEADER = checker.h

PUSH_SWAP_SRCDIR = srcs/push_swap
CHECKER_SRCDIR = srcs/checker
GENERATOR_SRCDIR = srcs/generator
OBJDIR = objs
INCDIR = includes
LIBDIR = libft/includes
LIBFT_HEADER = $(LIBDIR)

CFLAGS = -Wall -Werror -Wextra -I$(INCDIR) -I$(LIBFT_HEADER)

PUSH_SWAP_SRC		= ft_special_secure_atoi get_next_line push_swap parser lib op_push op_swap op_rev op_rrev tools rationalize nao_q_sort nao_q_sort_aux nao_short_list load_file
CHECKER_SRC			= ft_special_secure_atoi checker parser lib sort op_swap op_push op_rev op_rrev get_next_line load_file
GENERATOR_SRC		= generator

TMP_A = $(basename $(notdir $(PUSH_SWAP_SRC)))
TMP_B = $(basename $(notdir $(CHECKER_SRC)))
TMP_C = $(basename $(notdir $(GENERATOR_SRC)))

PUSH_SWAP_OBJ = $(addprefix $(OBJDIR)/push_swap/, $(addsuffix .o, $(TMP_A)))
CHECKER_OBJ = $(addprefix $(OBJDIR)/checker/, $(addsuffix .o, $(TMP_B)))
GENERATOR_OBJ = $(addprefix $(OBJDIR)/generator/, $(addsuffix .o, $(TMP_C)))

.PHONY: all clean fclean re help

all: $(NAME)

push_swap: $(PUSH_SWAP_OBJ) $(INCDIR)/$(PUSH_SWAP_HEADER)
	make -C libft/ all
	$(CC) $(CFLAGS) -o push_swap $(PUSH_SWAP_OBJ) -L./libft -lft

checker: $(CHECKER_OBJ) $(INCDIR)/$(CHECKER_HEADER)
	make -C libft/ all
	$(CC) $(CFLAGS) -o checker $(CHECKER_OBJ) -L./libft -lft

generator: $(GENERATOR_OBJ)
	$(CC) $(CFLAGS) -o generator $(GENERATOR_OBJ)

$(OBJDIR)/push_swap/%.o: $(PUSH_SWAP_SRCDIR)/%.c $(INCDIR)/$(PUSH_SWAP_HEADER)
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/checker/%.o: $(CHECKER_SRCDIR)/%.c $(INCDIR)/$(CHECKER_HEADER)
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/generator/%.o: $(GENERATOR_SRCDIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	make -C libft/ clean
	rm -vf $(PUSH_SWAP_OBJ)
	rm -vf $(CHECKER_OBJ)
	rm -vf $(GENERATOR_OBJ)

fclean: clean
	make -C libft/ fclean
	rm -vf $(NAME)

re: 	fclean all

help:
	@echo
	@echo "Programm $(NAME)"
	@echo
	@echo "--------------------------------------------------------------------------"
	@echo " Disp rules."
	@echo
	@echo " all     : Compile the programm $(NAME) into $(BINDIR) directory."
	@echo " re      : Recompile all objets of the programm."
	@echo " clean   : Remove objects."
	@echo " fclean  : Remove objects and programm."
	@echo " help    : Display this."
	@echo "--------------------------------------------------------------------------"
	@echo
