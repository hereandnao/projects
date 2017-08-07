/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:13:41 by saubenne          #+#    #+#             */
/*   Updated: 2016/11/05 15:25:00 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char	*destination;
	char	*source;
	size_t	i;

	destination = (char*)(dest);
	source = (char*)(src);
	i = 0;
	while (i < n)
	{
		destination[i] = source[i];
		if (source[i] == c)
			return (destination + i + 1);
		i++;
	}
	return (NULL);
}
