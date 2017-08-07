/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:49:30 by saubenne          #+#    #+#             */
/*   Updated: 2016/11/07 13:06:13 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**tab_words(const char *s, char c)
{
	int		i;
	int		t;
	int		n;
	char	**tab;

	i = 0;
	n = 0;
	t = 0;
	while (s[i])
	{
		if (t == 0 && s[i] != c)
		{
			t = 1;
			n = n + 1;
		}
		if (s[i] == c)
			t = 0;
		i++;
	}
	if (!(tab = (char **)malloc((n + 1) * sizeof(char *))))
		return (NULL);
	tab[n] = NULL;
	return (tab);
}

static int		l_num(const char *s, char c)
{
	int i;
	int l;

	i = 0;
	l = 0;
	while (s[i])
	{
		if (s[i] != c)
			l++;
		else
			return (l);
		i++;
	}
	return (l);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		w;
	int		i;

	if (!(tab = tab_words(s, c)))
		return (NULL);
	w = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			i = 0;
			if (!(tab[w] = (char *)malloc((l_num(s, c) + 1) * sizeof(char))))
				return (NULL);
			while (*s != c && *s != '\0')
				tab[w][i++] = *s++;
			tab[w++][i] = '\0';
		}
	}
	return (tab);
}
