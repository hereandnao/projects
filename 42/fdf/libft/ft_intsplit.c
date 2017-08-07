/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:49:30 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/02 14:18:34 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		*tab_int(const char *s, char c, size_t *size)
{
	int		i;
	int		t;
	int		*tab;

	i = 0;
	t = 0;
	*size = 0;
	while (s[i])
	{
		if (t == 0 && s[i] != c)
		{
			t = 1;
			*size = *size + 1;
		}
		if (s[i] == c)
			t = 0;
		i++;
	}
	if (!(tab = (int *)malloc((*size) * sizeof(int))))
		return (NULL);
	return (tab);
}

int				*ft_intsplit(char const *s, char c, size_t *size)
{
	int		*tab;
	int		w;

	if (!(tab = tab_int(s, c, size)))
		return (NULL);
	w = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			tab[w++] = ft_atoi(s);
			while (*s != c && *s != '\0')
				s++;
		}
	}
	return (tab);
}
