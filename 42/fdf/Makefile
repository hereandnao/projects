#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saubenne <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/23 15:41:46 by saubenne          #+#    #+#              #
#    Updated: 2017/05/04 14:38:15 by saubenne         ###   ########.fr        #
#                                                                              #
#******************************************************************************#
NAME = fdf
CC = gcc
HEADER = fdf.h

SRCDIR = ./srcs
BINDIR = ./
OBJDIR = ./objs
INCDIR = ./includes
LIBDIR = ./libft
LIBFT_HEADER = $(LIBDIR)

CFLAGS = -Wall -Werror -Wextra -I$(INCDIR) -I./minilibx_macos -I$(LIBFT_HEADER)

SRC		= fdf draw_line load minilib s_atoi draw_all eval_map

TMP = $(basename $(notdir $(SRC)))
OBJ = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(TMP)))

.PHONY: all clean fclean re help

all: $(NAME)

$(NAME): $(OBJ) $(INCDIR)/$(HEADER)
	make -C minilibx_macos/ all
	make -C libft/ all
	$(CC) $(CFLAGS) -o $(BINDIR)/$(NAME) $(OBJ) -L./libft -lft -lmlx -framework openGL -framework AppKit

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/$(HEADER)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	make -C minilibx_macos/ clean
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
