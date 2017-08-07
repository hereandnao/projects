/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 14:05:44 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/25 14:05:47 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		naosize(int n)
{
	size_t len;

	len = 0;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len + 1);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		negatif;

	i = 0;
	negatif = (n < 0) ? 1 : 0;
	if (!(str = ft_strnew(naosize(n))))
		return (NULL);
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (n != 0)
	{
		if (negatif)
			str[i] = ('0' - (n % 10));
		else
			str[i] = ((n % 10) + '0');
		n = n / 10;
		i++;
	}
	if (negatif)
		str[i] = '-';
	return (ft_strrev(str));
}
