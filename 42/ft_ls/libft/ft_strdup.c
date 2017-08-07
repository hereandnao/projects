/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 14:10:00 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/25 14:10:04 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		len;

	len = ft_strlen(s1);
	dest = (char*)malloc((len + 1) * sizeof(*dest));
	if (dest == NULL)
		return (NULL);
	dest = ft_strcpy(dest, s1);
	return (dest);
}
