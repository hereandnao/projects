/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:49:22 by saubenne          #+#    #+#             */
/*   Updated: 2016/11/08 17:05:36 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*s_getbegin(char *s)
{
	char *origin;

	origin = s;
	while (*s)
	{
		if (*s != ' ' && *s != '\t' && *s != '\n')
			return (s);
		s++;
	}
	return (origin);
}

static char		*s_getend(char *s)
{
	size_t size;

	if (!(size = ft_strlen(s)))
		return (s);
	s = s + size;
	while (size--)
	{
		s--;
		if (*s != ' ' && *s != '\t' && *s != '\n')
			return (s + 1);
	}
	return (s);
}

char			*ft_strtrim(const char *s)
{
	char *ptrbeg;
	char *ptrend;
	char *str;
	char *begin;

	ptrbeg = s_getbegin((char*)s);
	ptrend = s_getend((char*)s);
	if (!(str = ft_strnew((size_t)ptrend - (size_t)ptrbeg)))
		return (NULL);
	begin = str;
	while (ptrbeg < ptrend)
		*str++ = *ptrbeg++;
	return (begin);
}
