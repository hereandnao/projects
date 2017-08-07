/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 23:01:29 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/15 23:01:32 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"

unsigned int		l2b(unsigned int a)
{
	return ((a << 24) + ((a & 0x0000FF00) << 8) +
		((a & 0x00FF0000) >> 8) + (a >> 24));
}

char				*clean_content_memory(char **content, char *err)
{
	int i;

	i = 0;
	while (content[i])
		free(content[i++]);
	free(content);
	return (err);
}

void				write_direct_value(char *s, int n, int x)
{
	if (x == 2)
	{
		n = ((n & 0x00FF) << 8) + ((n & 0xFF00) >> 8);
		ft_memcpy(s, &n, 2);
	}
	else
	{
		n = ((n & 0xFF000000) >> 24) + ((n & 0x00FF0000) >> 8) +
		((n & 0x0000FF00) << 8) + ((n & 0x000000FF) << 24);
		ft_memcpy(s, &n, 4);
	}
}

int					debug_result(t_map *map)
{
	if (!map->name)
	{
		ft_eprintf(ERR_NAME);
		return (0);
	}
	else if (!ft_strlen(map->buff + 4))
	{
		ft_eprintf(ERR_NO_NAME);
		return (0);
	}
	else if (!map->comment)
	{
		ft_eprintf(ERR_COMMENT);
		return (0);
	}
	else if (map->ptr == (map->buff + sizeof(t_header)))
	{
		ft_eprintf(ERR_VOID);
		return (0);
	}
	return (1);
}

int					is_label_char(char c)
{
	size_t n;
	size_t i;

	n = ft_strlen(LABEL_CHARS);
	i = 0;
	while (i < n)
	{
		if (c == LABEL_CHARS[i])
			return (1);
		i++;
	}
	return (0);
}
