/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 14:14:22 by saubenne          #+#    #+#             */
/*   Updated: 2017/03/06 14:06:51 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_charsize(wchar_t c)
{
	if (c >= 0 && c <= 128)
		return (1);
	else if (c > 0 && c <= 2048)
		return (2);
	else if (c > 0 && c <= 65536)
		return (3);
	else if (c > 0 && c <= INT_MAX)
		return (4);
	return (-1);
}

int				nao_uchar(va_list *ap, t_flags *args)
{
	wchar_t			c;
	char			*str;
	int				size;

	str = NULL;
	c = (wchar_t)va_arg(*ap, wchar_t);
	size = get_charsize(c);
	if (args->width < size)
		args->width = size;
	str = ft_strnew(args->width);
	if (args->mask & minus)
	{
		ft_memset(str + size, ' ', args->width - size);
		ft_putwchar(c, str);
	}
	else
	{
		ft_memset(str, (args->mask & zero) ? '0' : ' ', args->width - size);
		ft_putwchar(c, str + args->width - size);
	}
	write(1, str, args->width);
	free(str);
	return (args->width);
}
