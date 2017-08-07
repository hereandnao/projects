/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 15:01:36 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/18 15:01:37 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnjoin(char *s1, char *s2, int n)
{
	int		lens1;
	char	*str;

	if (s1 == NULL)
	{
		if (!(str = (char*)malloc((n + 1) * sizeof(*str))))
			return (NULL);
		str = ft_strncpy(str, s2, n);
		str[n] = '\0';
		return (str);
	}
	lens1 = ft_strlen(s1);
	if (!(str = (char *)malloc((lens1 + n + 1) * sizeof(*str))))
		return (NULL);
	ft_strcpy(str, s1);
	free(s1);
	str = str + lens1;
	ft_strncpy(str, s2, n);
	str[n] = '\0';
	return (str - lens1);
}
