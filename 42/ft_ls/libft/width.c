/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 15:17:17 by saubenne          #+#    #+#             */
/*   Updated: 2017/03/06 15:20:55 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_width(char *str, va_list *ap, t_flags *args)
{
	int width;
	int i;

	width = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
			return (0);
		if (str[i] == '*')
		{
			width = va_arg(*ap, int);
			if (width < 0)
			{
				args->mask = args->mask | minus;
				width = width * (-1);
			}
			return (width);
		}
		if (str[i] >= '1' && str[i] <= '9')
			break ;
		i++;
	}
	width = (ft_isdigit(str[i]) == 1) ? ft_atoi(str + i) : width;
	return (width);
}

int		get_preci(char *str, va_list *ap)
{
	int	preci;
	int i;

	preci = -1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
			break ;
		i++;
	}
	if (str[i] && str[i + 1] == '*')
	{
		preci = va_arg(*ap, int);
		return ((preci < 0) ? -1 : preci);
	}
	if (str[i] != '\0')
		preci = ft_atoi(str + i + 1);
	return (preci);
}
