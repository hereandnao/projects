# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avideau <avideau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 17:08:29 by avideau           #+#    #+#              #
#    Updated: 2016/11/30 12:55:12 by avideau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRCS_PREFIX = srcs/
SRCS = main ft_putstr ft_strlen ft_map ft_lst ft_putchar \
	   ft_matrice ft_solve ft_generate \
	   ft_print ft_pose ft_getsize

SRCS := $(addsuffix .c, $(SRCS))
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror


all: $(NAME)

$(NAME):
	gcc $(FLAGS) -c $(addprefix $(SRCS_PREFIX), $(SRCS)) -I ./includes/
	gcc $(FLAGS) -o $(NAME) $(addprefix $(SRCS_PREFIX), $(SRCS)) -I ./includes/

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
