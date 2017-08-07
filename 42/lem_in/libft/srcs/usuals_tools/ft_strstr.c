/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 15:57:15 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/10 15:59:34 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t len;

	if (!(len = ft_strlen(little)))
		return ((char *)big);
	while (*big)
	{
		if (*big == *little)
		{
			if (ft_strncmp(big, little, len) == 0)
				return ((char *)big);
		}
		big++;
	}
	return (NULL);
}
