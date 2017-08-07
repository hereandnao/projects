/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:13:35 by saubenne          #+#    #+#             */
/*   Updated: 2016/11/05 15:21:57 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*destination;
	char	*source;
	size_t	i;

	destination = (char *)dest;
	source = (char *)src;
	i = 0;
	while (i < n)
	{
		*destination = *source;
		source++;
		destination++;
		i++;
	}
	return (dest);
}
