/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:32:18 by saubenne          #+#    #+#             */
/*   Updated: 2017/03/06 14:28:16 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <inttypes.h>
# include <wchar.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>

# define NUM_OF_FUNCTIONS 16

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

int				check_if_l(t_flags *args);
int				nao_string(va_list *ap, t_flags *args);
int				nao_char(va_list *ap, t_flags *args);
int				ft_printf(const char *s, ...);
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
