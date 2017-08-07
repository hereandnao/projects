#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saubenne <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/05 14:19:54 by saubenne          #+#    #+#              #
#    Updated: 2017/04/20 03:37:26 by saubenne         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	= libft.a

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra
HEADER = libft.h

SRC_PREFIX = ./

SRC		= ft_atoi ft_bzero ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_memalloc ft_memcpy ft_memccpy ft_memmove ft_memset \
		ft_memchr ft_memcmp ft_strcat ft_strchr ft_strncat ft_strlcat ft_strstr ft_strnstr ft_strrchr ft_tolower ft_toupper \
		ft_putchar ft_putchar_fd ft_putstr ft_putstr_fd ft_putendl ft_putendl_fd ft_putnbr ft_putnbr_fd ft_strdel \
		ft_strjoin ft_strsplit ft_intsplit ft_strsub ft_fstrsub ft_strtrim ft_strnjoin \
		ft_strequ ft_strnequ ft_strcmp ft_strncmp ft_strcpy ft_strncpy ft_strdup ft_strlen \
		ft_memdel ft_strnew ft_strclr ft_striter ft_striteri ft_strmap ft_strmapi ft_itoa \
		ft_lstnew ft_lstdelone ft_lstdel ft_lstadd ft_lstiter ft_lstmap \
		get_next_line \
		parse_flags \
		ft_printf fill_struct width cast \
		print_string print_char print_bin print_unsigned print_int print_hex print_oct \
		print_unicode print_point print_pourcent print_uchar \
		intsize ft_strcpy get_ustr \
		err_bin err_char err_int err_hex err_oct err_point err_pourcent \
		err_string err_uchar err_unicode err_unsigned err_printf \
		ft_lstinvert

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix $(SRC_PREFIX), $(SRC))

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	ar rc $(NAME) $(OBJ) $(HEADER)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	/bin/rm -f ${OBJ}

fclean:
	/bin/rm -f ${OBJ}
	/bin/rm -f $(NAME)

re: fclean all
