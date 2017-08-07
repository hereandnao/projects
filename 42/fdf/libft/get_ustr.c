/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ustr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:05:11 by saubenne          #+#    #+#             */
/*   Updated: 2017/02/18 16:05:14 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*get_ustr(int fd_s, t_flags *args, int nb_s)
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
