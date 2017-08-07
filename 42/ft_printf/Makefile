NAME	= libftprintf.a

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra

SRC_PREFIX = ./

SRC		=	parse_flags \
	 	ft_printf fill_struct width cast \
	 	print_string print_char print_bin print_unsigned print_int print_hex print_oct \
	 	print_unicode print_point print_pourcent print_uchar \
	 	ft_bzero ft_atoi ft_memcpy ft_memalloc ft_memmove ft_memset \
	 	ft_strrev ft_strchr ft_strlen ft_strncpy \
	 	ft_strnew ft_isdigit intsize ft_strcpy get_ustr intsize

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
