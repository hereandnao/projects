/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:26:34 by saubenne          #+#    #+#             */
/*   Updated: 2016/11/07 12:51:30 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lensrc;
	size_t	lendst;
	int		i;

	i = 0;
	lensrc = ft_strlen(src);
	lendst = ft_strlen(dst);
	if (lendst >= size || size == 0)
		return (size + lensrc);
	dst = ft_strncat(dst, src, (size - lendst - 1));
	return (lendst + lensrc);
}
