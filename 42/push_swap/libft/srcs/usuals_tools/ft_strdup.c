/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 15:02:06 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/10 20:40:02 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*output;
	char	*origin;
	size_t	s_mlen;

	origin = (char *)s1;
	while (*origin)
		origin++;
	s_mlen = origin - s1 + 1;
	if ((output = (char *)malloc(s_mlen * sizeof(char))))
	{
		origin = output;
		while (*s1)
			*output++ = *s1++;
		*output = '\0';
		return (origin);
	}
	return (NULL);
}
