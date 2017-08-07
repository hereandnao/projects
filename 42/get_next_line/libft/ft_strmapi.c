/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:48:48 by saubenne          #+#    #+#             */
/*   Updated: 2016/11/07 12:54:02 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	unsigned int	i;
	char			*retour;

	i = 0;
	len = (ft_strlen(s));
	if (!(retour = ft_strnew(len)))
		return (NULL);
	while (s[i])
	{
		retour[i] = f(i, (char)s[i]);
		i++;
	}
	return (retour);
}
