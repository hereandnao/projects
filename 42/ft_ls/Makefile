#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saubenne <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/25 14:31:11 by saubenne          #+#    #+#              #
#    Updated: 2017/04/25 14:31:15 by saubenne         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ls
CC = gcc
HEADER = ft_ls.h

CURRENT_DIRECTORY := $(shell pwd)
SRCDIR = $(CURRENT_DIRECTORY)
BINDIR = $(CURRENT_DIRECTORY)
OBJDIR = $(CURRENT_DIRECTORY)
INCDIR = $(CURRENT_DIRECTORY)
LIBDIR = $(CURRENT_DIRECTORY)/libft
LIBFT_HEADER = $(LIBDIR)

CFLAGS = -Wall -Werror -Wextra -I./ -I$(LIBFT_HEADER)

SRC		= ft_ls recurse parse print no_recurse sort sort_2 long_display get_info lib get_print_info fill

TMP = $(basename $(notdir $(SRC)))
OBJ = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(TMP)))

.PHONY: all clean fclean re help

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C libft/ all
	$(CC) $(CFLAGS) -o $(BINDIR)/$(NAME) $(OBJ) -L./libft -lft

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER)
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
