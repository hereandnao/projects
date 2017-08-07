/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:13:51 by saubenne          #+#    #+#             */
/*   Updated: 2016/11/08 21:33:19 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	i = len;
	if (len == 0)
		return (dst);
	if (src == dst)
		return (dst);
	if (src < dst)
	{
		while (i--)
			((char *)dst)[i] = ((const char *)src)[i];
		((char *)dst)[0] = ((const char *)src)[0];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			((char*)dst)[i] = ((const char*)src)[i];
			i++;
		}
	}
	return (dst);
}
