/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:49:17 by saubenne          #+#    #+#             */
/*   Updated: 2016/11/07 13:00:38 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s1);
	if (!(str = (char *)malloc((len + ft_strlen(s2) + 1) * sizeof(*str))))
		return (NULL);
	ft_strcpy(str, s1);
	str = str + len;
	ft_strcpy(str, s2);
	str[ft_strlen(s2)] = '\0';
	str = str - len;
	return (str);
}
