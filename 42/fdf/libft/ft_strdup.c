/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 15:02:06 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/10 20:40:02 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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
