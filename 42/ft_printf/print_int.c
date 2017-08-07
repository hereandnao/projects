/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 14:43:46 by saubenne          #+#    #+#             */
/*   Updated: 2017/02/18 14:34:54 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*get_string(int fd_s, t_flags *args, int nb_s)
{
	char *str;

	if (!(str = malloc(fd_s * sizeof(char))))
		return (NULL);
	if ((args->mask & zero) && (!(args->mask & minus)))
	{
		if (args->preci == -1)
		{
			ft_memset(str, '0', fd_s);
		}
		else
			ft_memset(str, ' ', fd_s);
	}
	else if (args->mask & minus)
		ft_memset(str + nb_s, ' ', fd_s - nb_s);
	else
		ft_memset(str, ' ', fd_s);
	return (str);
}

static void		write_num(char *str, intmax_t res, int nb_s)
{
	nb_s--;
	if (res < 0)
	{
		while (nb_s >= 0)
		{
			str[nb_s] = (-(res % 10)) + '0';
			res = res / 10;
			nb_s--;
		}
	}
	else
	{
		while (nb_s >= 0)
		{
			str[nb_s] = res % 10 + '0';
			res = res / 10;
			nb_s--;
		}
	}
}

static int		add_one(int nb_s, t_flags *args, intmax_t res)
{
	nb_s = (nb_s < args->preci) ? args->preci : nb_s;
	if (args->preci == -1 && res == 0)
		nb_s = nb_s + 1;
	if ((res >= 0) && (args->mask & plus))
		nb_s = nb_s + 1;
	else if (res < 0)
		nb_s = nb_s + 1;
	else if (res >= 0 && (args->mask & space))
		nb_s = nb_s + 1;
	return (nb_s);
}

static char		*add_sign(intmax_t res, t_flags *args, char *str, int sous)
{
	if (res >= 0)
	{
		if (args->mask & plus)
		{
			if (args->mask & minus)
				str[0] = '+';
			else
				str[sous] = '+';
		}
		else if (args->mask & space)
		{
			if (args->mask & minus)
				str[0] = ' ';
			else
				str[sous] = ' ';
		}
	}
	else
	{
		if ((minus & args->mask) || (args->width == 0 && args->preci == -1))
			str[0] = '-';
		else
			str[sous] = '-';
	}
	return (str);
}

int				nao_int(va_list *ap, t_flags *args)
{
	char		*str;
	intmax_t	res;
	int			fd_s;
	int			nb_s;

	res = va_arg(*ap, intmax_t);
	d_type(&res, args);
	nb_s = intsize(res, 0);
	nb_s = add_one(nb_s, args, res);
	fd_s = (args->width <= args->preci) ? args->preci : args->width;
	fd_s = nb_s < fd_s ? fd_s : nb_s;
	if ((args->mask & zero) && (args->preci == -1) && (!(args->mask & minus)))
		nb_s = fd_s;
	if (!(str = get_string(fd_s, args, nb_s)))
		return (-1);
	if (args->mask & minus)
		write_num(str, res, nb_s);
	else
		write_num(str + fd_s - nb_s, res, nb_s);
	str = add_sign(res, args, str, fd_s - nb_s);
	fd_s = write(1, str, fd_s);
	free(str);
	return (fd_s);
}
