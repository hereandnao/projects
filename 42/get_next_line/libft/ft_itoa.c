/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:49:38 by saubenne          #+#    #+#             */
/*   Updated: 2016/11/08 17:12:18 by saubenne         ###   ########.fr       */
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

static char		*ft_strrev(char *str)
{
	int		i;
	int		l;
	char	tmp;

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
