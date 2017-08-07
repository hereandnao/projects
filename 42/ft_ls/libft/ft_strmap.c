/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:46:54 by saubenne          #+#    #+#             */
/*   Updated: 2016/11/07 10:45:23 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	len;
	char	*retour;
	char	*debut;

	if (!(len = (ft_strlen(s))))
		return (NULL);
	if (!(retour = ft_strnew(len)))
		return (NULL);
	debut = retour;
	while (*s)
	{
		*retour = f((char)*s);
		retour++;
		s++;
	}
	return (debut);
}
