/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 14:10:44 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/25 14:10:45 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <inttypes.h>
# include <wchar.h>
# include <limits.h>

# define BUFF_SIZE 96
# define NUM_OF_FUNCTIONS 16
# define TRUE 1
# define FALSE 0

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef	struct	s_flags
{
	char			c;
	unsigned char	mask;
	int				preci;
	int				width;
	unsigned char	len;
	unsigned char	if_lhjz;
}				t_flags;

typedef struct	s_fn
{
	char	c;
	int		(*f)(va_list *, t_flags *);
}				t_fn;
t_list			*ft_lstinvert(t_list **alst);
void			*ft_memset(void *str, int c, size_t n);
void			ft_bzero(void *str, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);

size_t			ft_strlen(const char *str);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *str1, const char *str2, size_t num);
char			*ft_strstr(const char *s1, const char *s2);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *s, int c);
size_t			ft_strlcat(char *dest, const char *src, size_t dest_size);
char			*ft_strncat (char *dest, const char *src, size_t n);
char			*ft_strnstr(char *s1, const char *s2, size_t n);

char			*ft_strdup(const char *s1);
int				ft_atoi(const char *nptr);

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isalnum(int c);

int				ft_toupper(int c);
int				ft_tolower(int c);

void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putstr(char const *s);

void			*ft_memalloc(size_t size);

void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);

int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_strsplit(char const *s, char c);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_fstrsub(char *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s);
char			*ft_strnjoin(char *s1, char *s2, int n);

void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char(*f)(unsigned int, char));

char			*ft_itoa(int n);

t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

int				get_next_line(int const fd, char **line);
int				find_word(int const fd, char **line, char *needle);

int				check_if_l(t_flags *args);
int				nao_string(va_list *ap, t_flags *args);
int				nao_char(va_list *ap, t_flags *args);
int				ft_printf(const char *s, ...);
int				err_printf(const char *s, ...);
char			*get_letter(char *str);
unsigned char	flag_analyzer(char *str);
int				get_width(char *str, va_list *ap, t_flags *args);
int				get_preci(char *str, va_list *ap);
unsigned char	convert_detector(char *sub, unsigned char flag);
void			x_type(uintmax_t *res, t_flags *args);
void			i_type(intmax_t *res, t_flags *args);
void			o_type(uintmax_t *res, t_flags *args);
void			b_type(uintmax_t *res, t_flags *args);
void			d_type(intmax_t *res, t_flags *args);

int				nao_unsigned(va_list *ap, t_flags *args);
int				nao_int(va_list *ap, t_flags *args);
int				nao_x(va_list *ap, t_flags *args);
int				nao_o(va_list *ap, t_flags *args);
int				nao_b(va_list *ap, t_flags *args);

intmax_t		intsize(intmax_t n, int nb_s);
int				nao_uchar(va_list *ap, t_flags *args);
int				nao_pourcent(va_list *ap, t_flags *args);
int				nao_p(va_list *ap, t_flags *args);
t_flags			fill_struct(t_flags args, char *sub, va_list *ap);
int				nao_uchar(va_list *ap, t_flags *args);

int				err_string(va_list *ap, t_flags *args);
int				err_unsigned(va_list *ap, t_flags *args);
int				err_int(va_list *ap, t_flags *args);
int				err_x(va_list *ap, t_flags *args);
int				err_o(va_list *ap, t_flags *args);
int				err_b(va_list *ap, t_flags *args);
int				err_uchar(va_list *ap, t_flags *args);
int				err_pourcent(va_list *ap, t_flags *args);
int				err_p(va_list *ap, t_flags *args);
int				err_uchar(va_list *ap, t_flags *args);
int				err_char(va_list *ap, t_flags *args);

int				ft_putwchar(wchar_t c, char *str);
int				ft_putwstr(wchar_t *str);
char			*get_ustr(int fd_s, t_flags *args, int nb_s);

int				ft_atoi(const char *nptr);
void			ft_bzero(void *str, size_t n);
void			*ft_memset(void *str, int c, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
size_t			ft_strlen(const char *str);

int				ft_isdigit(int c);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strnew(size_t size);
void			*ft_memalloc(size_t size);
char			*ft_strrev(char *str);

char			*ft_strchr(const char *str, int c);

enum	e_convert{
	if_l = 0x01,
	if_ll = 0x02,
	if_h = 0x04,
	if_hh = 0x08,
	if_j = 0x10,
	if_z = 0x20,
};

enum	e_flags{
	hash = 0x01,
	zero = 0x02,
	minus = 0x04,
	plus = 0x08,
	space = 0x10,
};

#endif
