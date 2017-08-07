/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 14:52:07 by saubenne          #+#    #+#             */
/*   Updated: 2017/02/18 14:43:06 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*add_prefix(char *str, t_flags *args, int fd_s, int nb_s)
{
	if ((args->mask & hash))
	{
		if (args->mask & minus)
		{
			if ((args->c == 'x') || (args->c == 'p'))
				ft_memcpy(str, "0x", 2);
			else
				ft_memcpy(str, "0X", 2);
		}
		else
		{
			if (args->c == 'x' || args->c == 'p')
				ft_memcpy(str + fd_s - nb_s, "0x", 2);
			else
				ft_memcpy(str + fd_s - nb_s, "0X", 2);
		}
	}
	return (str);
}

static char		*get_hexstr(int fd_s, t_flags *args, int nb_s)
{
	char *str;

	if (!(str = malloc(fd_s * sizeof(char))))
		return (NULL);
	if ((args->mask & zero) && (!(args->mask & minus)))
	{
		if (args->preci == -1)
			ft_memset(str, '0', fd_s);
		else
			ft_memset(str, ' ', fd_s);
	}
	else if (args->mask & minus)
		ft_memset(str + nb_s, ' ', fd_s - nb_s);
	else
		ft_memset(str, ' ', fd_s);
	return (str);
}

static int		gethexsize(uintmax_t nb)
{
	int i;

	i = 1;
	while ((nb = nb >> 4))
		i++;
	return (i);
}

static void		wrt_x(char *str, uintmax_t res, int nb_s, char c)
{
	int			mod;
	uintmax_t	quot;

	mod = 0;
	quot = res;
	while (nb_s--)
	{
		mod = quot & 0xF;
		if (mod < 10)
			mod = mod + 48;
		else
		{
			if (c == 'x' || c == 'p')
				mod = mod + 87;
			else if (c == 'X')
				mod = mod + 55;
		}
		str[nb_s] = mod;
		quot = quot >> 4;
	}
}

int				nao_p(va_list *ap, t_flags *args)
{
	char		*str;
	uintmax_t	res;
	int			nb_s;
	int			fd_s;

	res = va_arg(*ap, uintmax_t);
	res = (unsigned long)res;
	args->mask = args->mask | hash;
	nb_s = gethexsize(res);
	nb_s = (nb_s < args->preci) ? args->preci : nb_s;
	if (((args->mask & hash) && (res != 0)) || (args->c == 'p'))
		nb_s = nb_s + 2;
	nb_s = ((args->preci == 0) && (res == 0)) ? 2 : nb_s;
	fd_s = (args->width <= args->preci) ? args->preci : args->width;
	fd_s = nb_s < fd_s ? fd_s : nb_s;
	if ((args->mask & zero) && (args->preci == -1) && (!(args->mask & minus)))
		nb_s = fd_s;
	if (!(str = get_hexstr(fd_s, args, nb_s)))
		return (-1);
	wrt_x((args->mask & minus) ? str : str + fd_s - nb_s, res, nb_s, args->c);
	if (res != 0 || args->c == 'p')
		str = add_prefix(str, args, fd_s, nb_s);
	fd_s = write(1, str, fd_s);
	free(str);
	return (fd_s);
}
