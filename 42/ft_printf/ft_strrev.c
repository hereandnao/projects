/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 14:17:08 by saubenne          #+#    #+#             */
/*   Updated: 2017/02/18 14:17:11 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_strrev(char *str)
{
	int		i;
	int		l;
	char	tmp;

	if (str == NULL)
		return (NULL);
	if (str)
	{
		i = 0;
		l = ft_strlen(str);
		while (i < l / 2)
		{
			tmp = str[i];
			str[i] = str[l - i - 1];
			str[l - i - 1] = tmp;
			i++;
		}
	}
	return (str);
}
