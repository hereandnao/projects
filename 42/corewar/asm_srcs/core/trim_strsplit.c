/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_strsplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 23:22:47 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/15 23:22:50 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

static int		l_num_trimed(const char *s, char c, int *start, int *end)
{
	int i;
	int l;
	int j;

	i = 0;
	j = 0;
	l = 0;
	while (s[i] && s[i] != c && (s[i] == ' ' || s[i] == '\t'))
		i++;
	*start = i;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = (s[i] == ' ' || s[i] == '\t') ? j + 1 : 0;
			l++;
		}
		else
			break ;
		i++;
	}
	*end = j;
	return (l - j);
}

char			**trim_strsplit(char const *s, char c, int *n)
{
	char	**tab;
	int		start;
	int		end;
	size_t	size;

	if (!(tab = tab_words(s, c)))
		return (NULL);
	*n = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			if (!(tab[*n] = (char *)ft_memalloc(((
				size = l_num_trimed(s, c, &start, &end)) + 1) * sizeof(char))))
				return (NULL);
			ft_strncpy(tab[(*n)++], s + start, size);
			s += start + size + end;
		}
	}
	return (tab);
}
