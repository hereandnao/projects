/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:15:21 by saubenne          #+#    #+#             */
/*   Updated: 2016/11/07 13:02:06 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t len;

	len = ft_strlen(s2);
	if (len == 0)
		return ((char*)s1);
	while (*s1 != '\0')
	{
		if (ft_strncmp(s1, s2, len) == 0)
			return ((char*)s1);
		s1++;
	}
	return (NULL);
}
