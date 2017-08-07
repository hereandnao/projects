#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saubenne <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/05 14:19:54 by saubenne          #+#    #+#              #
#    Updated: 2016/12/17 17:53:24 by saubenne         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= libft.a

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -I./includes
SRC_PREFIX = ./

SRC		= ft_atoi ft_bzero ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_memalloc ft_memcpy ft_memccpy ft_memmove ft_memset \
		ft_memchr ft_memcmp ft_strcat ft_strchr ft_strncat ft_strlcat ft_strstr ft_strnstr ft_strrchr ft_tolower ft_toupper \
		ft_putchar ft_putchar_fd ft_putstr ft_putstr_fd ft_putendl ft_putendl_fd ft_putnbr ft_putnbr_fd ft_strdel \
		ft_strjoin ft_strsplit ft_strsub ft_strtrim \
		ft_strequ ft_strnequ ft_strcmp ft_strncmp ft_strcpy ft_strncpy ft_strdup ft_strlen \
		ft_memdel ft_strnew ft_strclr ft_striter ft_striteri ft_strmap ft_strmapi ft_itoa \
		ft_lstnew ft_lstdelone ft_lstdel ft_lstadd ft_lstiter ft_lstmap \

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix $(SRC_PREFIX), $(SRC))

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ) $(HEADER)

bin/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	/bin/rm -f ${OBJ}

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

