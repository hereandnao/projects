/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 14:59:56 by saubenne          #+#    #+#             */
/*   Updated: 2017/02/18 16:04:56 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			write_u(char *str, uintmax_t res, int nb_s)
{
	while (nb_s--)
	{
		str[nb_s] = res % 10 + '0';
		res = res / 10;
	}
}

static uintmax_t	nbsize(uintmax_t n, int len)
{
	if (n == 0)
		return (len);
	else
		return (nbsize(n / 10, len + 1));
}

static void			u_type(uintmax_t *res, t_flags *args)
{
	if ((args->if_lhjz & if_l) || (args->c == 'U'))
		*res = (unsigned long)*res;
	else if (args->if_lhjz == 0x00)
		*res = (unsigned int)*res;
	else if (args->if_lhjz & if_l)
		*res = (unsigned long)*res;
	else if (args->if_lhjz & if_ll)
		*res = (unsigned long long)*res;
	else if (args->if_lhjz & if_h)
		*res = (unsigned short)*res;
	else if (args->if_lhjz & if_hh)
		*res = (unsigned char)*res;
	else if (args->if_lhjz & if_z)
		*res = (size_t)*res;
}

static int			get_nbs(t_flags *args)
{
	if (args->preci == 0)
		return (0);
	return (1);
}

int					nao_unsigned(va_list *ap, t_flags *args)
{
	uintmax_t	res;
	int			fd_s;
	char		*str;
	int			nb_s;

	res = va_arg(*ap, uintmax_t);
	u_type(&res, args);
	nb_s = nbsize(res, 0);
	nb_s = (nb_s < args->preci) ? args->preci : nb_s;
	if (res == 0)
		nb_s = get_nbs(args);
	fd_s = (args->width <= args->preci) ? args->preci : args->width;
	fd_s = nb_s < fd_s ? fd_s : nb_s;
	if ((args->mask & zero) && (args->preci == -1) && (!(args->mask & minus)))
		nb_s = fd_s;
	if (!(str = get_ustr(fd_s, args, nb_s)))
		return (-1);
	write_u((args->mask & minus) ? str : str + fd_s - nb_s, res, nb_s);
	fd_s = write(1, str, fd_s);
	if (str)
		free(str);
	return (fd_s);
}
