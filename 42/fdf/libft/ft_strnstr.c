/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:16:29 by saubenne          #+#    #+#             */
/*   Updated: 2016/11/09 15:34:04 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(s2);
	if (len == 0)
		return ((char*)s1);
	while (*s1 && i <= (n - len))
	{
		if (n < len)
			return (NULL);
		if (ft_strncmp(s1, s2, len) == 0)
			return ((char*)s1);
		i++;
		s1++;
	}
	return (NULL);
}
