/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unicode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 14:56:25 by saubenne          #+#    #+#             */
/*   Updated: 2017/02/18 14:51:00 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Bytes|    c1      Format Output             |        Format Input         |
**   1  | 0xxxxxxx    c1                       | 00000000 00000000 0xxxxxxx  |
**   2  | 110yyyyy 10xxxxxx     c1             | 00000000 00000yyy yyxxxxxx  |
**   3  | 1110zzzz 10yyyyyy 10xxxxxx    c1     | 00000000 zzzzyyyy yyxxxxxx  |
**   4  | 11110www 10zzzzzz 10yyyyyy 10xxxxxx  | 000wwwzz zzzzyyyy yyxxxxxx  |
*/

static void	case_2(unsigned char *c, char *str)
{
	unsigned char c1;
	unsigned char c2;

	c1 = c[0];
	c2 = c[1];
	c2 <<= 2;
	c2 = c2 | (c1 >> 6);
	c1 = c1 & 0b00111111;
	c1 = c1 | 0b10000000;
	c2 = c2 & 0b00011111;
	c2 = c2 | 0b11000000;
	str[0] = c2;
	str[1] = c1;
}

static void	case_3(unsigned char *c, char *str)
{
	unsigned char			c1;
	unsigned char			c2;
	unsigned char			c3;

	c1 = c[0];
	c2 = c[1];
	c3 = c[2];
	c3 = c3 | (c2 >> 4);
	c3 = c3 & 0b00001111;
	c3 = c3 | 0b11100000;
	c2 = c2 << 2;
	c2 = c2 | (c1 >> 6);
	c1 = (c1 & 0b00111111) | 0b10000000;
	c2 = c2 & 0b00111111;
	c2 = c2 | 0b10000000;
	str[0] = c3;
	str[1] = c2;
	str[2] = c1;
}

static void	case_4(unsigned char *c, char *str)
{
	unsigned char			c1;
	unsigned char			c2;
	unsigned char			c3;
	unsigned char			c4;

	c1 = c[0];
	c2 = c[1];
	c3 = c[2];
	c4 = c[4];
	c4 = c4 | c3 >> 2;
	c3 = c3 << 4;
	c3 = c3 | (c2 >> 4);
	c3 = c3 & 0b00111111;
	c3 = c3 | 0b10000000;
	c2 = c2 << 2;
	c2 = c2 | (c1 >> 6);
	c1 = c1 & 0b00111111;
	c1 = c1 | 0b10000000;
	c2 = (c2 & 0b00111111) | 0b10000000;
	c4 = c4 & 0b00000111;
	c4 = c4 | 0b11110000;
	str[0] = c4;
	str[1] = c3;
	str[2] = c2;
	str[3] = c1;
}

int			ft_putwchar(wchar_t c, char *str)
{
	if (c > 0 && c <= 128)
	{
		str[0] = c;
		return (1);
	}
	else if (c > 0 && c <= 2048)
	{
		case_2((unsigned char*)&c, str);
		return (2);
	}
	else if (c > 0 && c <= 65536)
	{
		case_3((unsigned char*)&c, str);
		return (3);
	}
	else if (c > 0 && c <= INT_MAX)
	{
		case_4((unsigned char*)&c, str);
		return (4);
	}
	return (-1);
}
