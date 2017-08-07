/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 14:12:34 by saubenne          #+#    #+#             */
/*   Updated: 2017/02/18 14:21:27 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*add_prefix(char *str, t_flags *args, int fd_s, int nb_s)
{
	if (args->mask & hash)
	{
		if (args->mask & minus)
			ft_memcpy(str, "0b", 2);
		else
			ft_memcpy(str + fd_s - nb_s, "0b", 2);
	}
	return (str);
}

static char		*get_bins(int fd_s, t_flags *args, int nb_s)
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

static int		getbinsize(uintmax_t nb)
{
	int i;

	i = 1;
	while ((nb = nb >> 1))
		i++;
	return (i);
}

static void		write_bin(char *str, uintmax_t res, int nb_s)
{
	while (nb_s--)
	{
		str[nb_s] = (res % 2) + '0';
		res = res / 2;
	}
}

int				nao_b(va_list *ap, t_flags *args)
{
	char		*str;
	uintmax_t	res;
	int			nb_s;
	int			fd_s;

	res = va_arg(*ap, uintmax_t);
	b_type(&res, args);
	nb_s = getbinsize(res);
	nb_s = (nb_s < args->preci) ? args->preci : nb_s;
	if ((args->mask & hash) && (res != 0))
		nb_s = nb_s + 2;
	if ((args->preci == 0) && (res == 0))
		nb_s = 0;
	fd_s = (args->width <= args->preci) ? args->preci : args->width;
	fd_s = nb_s < fd_s ? fd_s : nb_s;
	if ((args->mask & zero) && (args->preci == -1) && (!(args->mask & minus)))
		nb_s = fd_s;
	if (!(str = get_bins(fd_s, args, nb_s)))
		return (-1);
	write_bin((args->mask & minus) ? str : str + fd_s - nb_s, res, nb_s);
	if (res != 0)
		str = add_prefix(str, args, fd_s, nb_s);
	fd_s = write(1, str, fd_s);
	free(str);
	return (fd_s);
}
