/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 14:53:19 by saubenne          #+#    #+#             */
/*   Updated: 2017/02/18 14:49:16 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		get_len(wchar_t *str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] > 0 && str[i] <= 128)
			len += 1;
		else if (str[i] > 0 && str[i] <= 2048)
			len += 2;
		else if (str[i] > 0 && str[i] <= 65536)
			len += 3;
		else if (str[i] > 0 && str[i] <= INT_MAX)
			len += 4;
		else
			break ;
		i++;
	}
	return (len);
}

static int		reallen(wchar_t *str, int realsize)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] > 0 && str[i] <= 128)
			j += 1;
		else if (str[i] > 0 && str[i] <= 2048)
			j += 2;
		else if (str[i] > 0 && str[i] <= 65536)
			j += 3;
		else if (str[i] > 0 && str[i] <= INT_MAX)
			j += 4;
		if (j <= realsize)
			len = j;
		else
			break ;
		i++;
	}
	return (len);
}

static void		write_uni(wchar_t *str, t_flags *args, char *res, int len)
{
	int i;
	int a;

	i = 0;
	if (args->mask & minus)
	{
		a = 0;
		while (a != len)
		{
			a += ft_putwchar(str[i], res + a);
			i++;
		}
	}
	else
	{
		a = args->width - len;
		while (a != args->width)
		{
			a += ft_putwchar(str[i], res + a);
			i++;
		}
	}
}

int				uni_string(va_list *ap, t_flags *args)
{
	wchar_t	*str;
	int		len;
	char	*res;

	str = va_arg(*ap, wchar_t *);
	if (str == NULL)
		str = L"(null)";
	len = (args->preci != -1) ? (reallen(str, args->preci)) : (get_len(str));
	if (args->width < len)
		args->width = len;
	if (!(res = ft_strnew(args->width)))
		return (-1);
	ft_memset(res, (!(args->mask & 0x04) && (args->mask & zero)) ?
		'0' : ' ', args->width);
	write_uni(str, args, res, len);
	args->width = write(1, res, args->width);
	free(res);
	return (args->width);
}

int				nao_string(va_list *ap, t_flags *args)
{
	char	*str;
	char	*res;
	int		len;

	if ((args->if_lhjz & 0x01) || (args->c == 'S'))
		return (uni_string(ap, args));
	str = va_arg(*ap, char *);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	if (args->preci != -1 && args->preci < len)
		len = args->preci;
	if (args->width < len)
		args->width = len;
	res = ft_strnew(args->width);
	ft_memset(res, (!(args->mask & 0x04) && (args->mask & zero)) ?
		'0' : ' ', args->width);
	args->mask & 0x04 ? ft_memcpy(res, str, len) :
		ft_memcpy(res + args->width - len, str, len);
	write(1, res, args->width);
	free(res);
	return (args->width);
}
