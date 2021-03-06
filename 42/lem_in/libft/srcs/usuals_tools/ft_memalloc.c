/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 16:32:53 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/26 01:25:29 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char *output;
	char *origin;

	if ((output = (char *)malloc(size * sizeof(char))))
	{
		origin = output;
		while (size--)
			*output++ = 0;
		return ((void *)origin);
	}
	return (NULL);
}
