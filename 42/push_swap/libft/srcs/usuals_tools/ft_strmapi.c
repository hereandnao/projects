/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 16:43:15 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/10 16:44:55 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	int		length;
	char	*output;
	int		i;

	length = ft_strlen(s);
	if ((output = (char *)malloc((length + 1) * sizeof(char))))
	{
		i = 0;
		while (i < length)
		{
			output[i] = f(i, s[i]);
			i++;
		}
		output[length] = '\0';
		return (output);
	}
	return (NULL);
}
