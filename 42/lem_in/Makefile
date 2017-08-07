#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saubenne <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/23 15:41:46 by saubenne          #+#    #+#              #
#    Updated: 2017/05/23 17:01:17 by saubenne         ###   ########.fr        #
#                                                                              #
#******************************************************************************#
NAME = lem-in
CC = gcc
HEADER = lemin.h

SRCDIR = ./srcs
BINDIR = ./
OBJDIR = ./objs
INCDIR = ./includes
LIBDIR = ./libft
LIBFT_HEADER = $(LIBDIR)/includes

CFLAGS = -Wall -Werror -Wextra -I $(INCDIR) -I $(LIBFT_HEADER)

SRC		= lemin get_room get_next_line manage_room get_links ft_special_secure_atoi resolver ants debugs check_coord get_args

TMP = $(basename $(notdir $(SRC)))
OBJ = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(TMP)))

.PHONY: all clean fclean re help

all: $(NAME)

$(NAME): $(OBJ) $(INCDIR)/$(HEADER)
	make -C libft/ all
	$(CC) $(CFLAGS) -o $(BINDIR)/$(NAME) $(OBJ) -L./libft -lft

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/$(HEADER)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	make -C libft/ clean
	rm -vf $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -vf $(NAME)

re: 	fclean all

help:
	@echo
	@echo "Program $(NAME)"
	@echo
	@echo "--------------------------------------------------------------------------"
	@echo " Display rules."
	@echo
	@echo " all     : Compile the program $(NAME) into $(BINDIR) directory."
	@echo " re      : Recompile all objects"
	@echo " clean   : Remove objects."
	@echo " fclean  : Remove objects and program."
	@echo " help    : Display this."
	@echo "--------------------------------------------------------------------------"
	@echo
