/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 16:48:13 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/10 16:48:56 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *output;
	char *origin;

	if ((output = (char *)malloc((len + 1) * sizeof(char))))
	{
		origin = output;
		s += start;
		while (len--)
			*output++ = *s++;
		*output = '\0';
		return (origin);
	}
	return (NULL);
}
