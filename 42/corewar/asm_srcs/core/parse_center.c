/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_center.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 23:35:30 by bmickael          #+#    #+#             */
/*   Updated: 2017/08/05 13:10:56 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"

/*
** Detecte les commentaires que ce soit en mode trimed_line or normal.
** Cette fonction possede une fonctionnalité spéciale en agissant sur
** le hook comment/name, tout ca à cause de la norme des 5 fonctions par
** fichiers shreugnegneu.
*/

static int		inline_comment(char *line, t_map *map)
{
	while (*line && (*line == '\t' || *line == ' '))
		line++;
	if (!*line || *line == ';' || *line == '#')
	{
		if (!map)
			return (1);
		map->comment = (map->hook == 2) ? TRUE : map->comment;
		map->name = (map->hook == 1) ? TRUE : map->name;
		map->hook = 0;
		return (1);
	}
	if (map)
		ft_eprintf((map->hook == 1) ? ERR_RAW_NAME : ERR_RAW_COMMENT);
	return (0);
}

static int		special_fill(char *line, char *content, t_map *map)
{
	char	*end_c;
	int		i;

	if (!(end_c = ft_strchr(line, '"')))
	{
		i = ft_strlen(line);
		if ((i + ft_strlen(content)) > (((map->hook == 1) ?
		PROG_NAME_LENGTH : COMMENT_LENGTH) - 1))
		{
			ft_eprintf((map->hook == 1) ? ERR_BIG_NAME : ERR_BIG_COMMENT);
			return (0);
		}
		ft_strncpy(content + ft_strlen(content), line, i);
		content[ft_strlen(content)] = '\n';
		return (1);
	}
	if (((i = end_c - line) + ft_strlen(content)) > ((map->hook == 1) ?
	PROG_NAME_LENGTH : COMMENT_LENGTH))
	{
		ft_eprintf((map->hook == 1) ? ERR_BIG_NAME : ERR_BIG_COMMENT);
		return (0);
	}
	ft_strncpy(content + ft_strlen(content), line, i);
	return (inline_comment(end_c + 1, map));
}

static int		extract_name(char *line, char *content, t_map *map)
{
	while (*line && (*line == '\t' || *line == ' '))
		line++;
	if (map->name || !(ft_strnequ(line, NAME_CMD_STRING, NAME_CMD_LENGTH)))
		return (0);
	line += NAME_CMD_LENGTH;
	while (*line && (*line == '\t' || *line == ' '))
		line++;
	if (*line != '"')
		return (0);
	map->hook = 1;
	return (special_fill(line + 1, content, map));
}

static int		extract_comment(char *line, char *content, t_map *map)
{
	while (*line && (*line == '\t' || *line == ' '))
		line++;
	if (map->comment ||
	!(ft_strnequ(line, COMMENT_CMD_STRING, COMMENT_CMD_LENGTH)))
		return (0);
	line += COMMENT_CMD_LENGTH;
	while (*line && (*line == '\t' || *line == ' '))
		line++;
	if (*line != '"')
		return (0);
	map->hook = 2;
	return (special_fill(line + 1, content, map));
}

int				parse_center(char *line, t_header *header, t_map *map, int n)
{
	int i;

	if (map->hook)
	{
		if (map->hook == 1)
			return (special_fill(line, header->prog_name, map));
		return (special_fill(line, header->comment, map));
	}
	if (inline_comment(line, NULL))
		return (1);
	if (!map->comment || !map->name)
		return (extract_name(line, header->prog_name, map)
		| extract_comment(line, header->comment, map));
		i = extract_instruction(line, map, n);
	if ((map->ptr - (map->buff + sizeof(t_header))) > CHAMP_MAX_SIZE)
	{
		ft_eprintf(ERR_TOO_BIG);
		return (0);
	}
	if (i == 0)
		ft_eprintf(BAD_ALLOCATION, line, n);
	return ((i <= 0) ? 0 : 1);
}
