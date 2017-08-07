/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fstrsub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:49:10 by saubenne          #+#    #+#             */
/*   Updated: 2016/11/05 15:39:39 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_fstrsub(char *s, unsigned int start, size_t len)
{
	char *str;
	char *debut;

	if (!(str = (char*)malloc((len + 1) * sizeof(*str))))
		return (NULL);
	debut = str;
	while (s[start] && len > 0)
	{
		*str = s[start];
		start++;
		str++;
		len--;
	}
	*str = '\0';
	return (debut);
}
