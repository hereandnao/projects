/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pourcent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 16:00:21 by saubenne          #+#    #+#             */
/*   Updated: 2017/02/17 16:00:45 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				nao_pourcent(va_list *ap, t_flags *args)
{
	char	*s;
	int		size;

	size = (args->width > 1) ? args->width : 1;
	if (!(s = malloc(size * sizeof(char))))
		return (-1);
	ft_memset(s, (args->mask & zero && !(args->mask & minus)) ?
		'0' : ' ', size);
	s[(args->mask & minus) ? 0 : size - 1] = '%';
	write(1, s, size);
	free(s);
	if (ap)
	{
	}
	return (size);
}
