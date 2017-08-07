/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_oct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 14:44:58 by saubenne          #+#    #+#             */
/*   Updated: 2017/02/18 14:36:01 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		write_oct(char *str, uintmax_t res, int nb_s)
{
	uintmax_t octal;

	octal = 0;
	while (nb_s--)
	{
		octal = res % 8;
		res = res / 8;
		str[nb_s] = octal + '0';
	}
}

static char		*add_prefix(char *str, t_flags *args, int fd_s, int nb_s)
{
	if (args->mask & hash)
	{
		if (args->mask & minus)
			ft_memcpy(str, "0", 1);
		else
			ft_memcpy(str + fd_s - nb_s, "0", 1);
	}
	return (str);
}

static char		*get_ostr(int fd_s, t_flags *args, int nb_s)
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

static int		get_osize(uintmax_t nb)
{
	int i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb = nb / 8;
		i++;
	}
	return (i);
}

int				nao_o(va_list *ap, t_flags *args)
{
	char		*str;
	uintmax_t	res;
	int			nb_s;
	int			fd_s;

	res = va_arg(*ap, uintmax_t);
	o_type(&res, args);
	nb_s = get_osize(res);
	if (args->preci == 0 && res == 0 && (!(args->mask & hash)))
		nb_s = 0;
	if ((res != 0 && (args->mask & hash)))
		nb_s = nb_s + 1;
	nb_s = (args->preci > nb_s) ? args->preci : nb_s;
	fd_s = (args->width > nb_s) ? args->width : nb_s;
	str = get_ostr(fd_s, args, nb_s);
	if (res != 0)
		str = add_prefix(str, args, fd_s, nb_s);
	write_oct((args->mask & minus) ? str :
		str + fd_s - nb_s, res, nb_s);
	fd_s = write(1, str, fd_s);
	free(str);
	return (fd_s);
}
