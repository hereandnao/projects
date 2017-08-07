/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 13:03:48 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/22 13:03:51 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				count_ants(int fd, t_map *map)
{
	char	*line;
	int		err;
	int		n;

	if (get_next_line(fd, &line) == -1)
		return (-1);
	if (line == NULL)
		return (-1);
	n = ft_secure_atoi(line, &err);
	if (err || n <= 0)
	{
		if (map->flags & VERBOSE)
			ft_printf("{red}Bad lemins count ! %s -> incorrect command\n{eoc}",
																		line);
		return (-1);
	}
	ft_printf("%s\n", line);
	free(line);
	return (n);
}

static int		check_room(t_room **rooms)
{
	t_room *current;

	current = *rooms;
	current = (*rooms)->next;
	while (current)
	{
		if (!(ft_strcmp(current->name, (*rooms)->name)))
		{
			delete_room(rooms);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

static char		*srch_fw(const char *s, int c)
{
	while (*s && *s != ' ' && *s != '\t')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0' && *s == '\0')
		return ((char *)s);
	return (NULL);
}

static int		p_set_to_false(int *start, int *end)
{
	*start = FALSE;
	*end = FALSE;
	return (1);
}

int				add_room(t_map *map, t_room **rooms, char *line, int *err)
{
	static int start = FALSE;
	static int end = FALSE;

	if (*line == 'L' || ((srch_fw(line, '-') != NULL && *line != '#')))
		return (0);
	if (ft_strcmp(line, "##start") == 0)
	{
		*err = (map->start || start || end) ? TRUE : *err;
		start = TRUE;
	}
	else if (ft_strcmp(line, "##end") == 0)
	{
		*err = (map->end || start || end) ? TRUE : *err;
		end = TRUE;
	}
	else if (*line && *line != '#' && *line != 'L' && (srch_fw(line, '-') == 0))
	{
		if ((*err = push_room(rooms, line, map)) ||
		(*err = check_room(rooms)))
			return (0);
		map->start = (start) ? *rooms : map->start;
		map->end = (end) ? *rooms : map->end;
		return (p_set_to_false(&start, &end));
	}
	return ((line[0] == '#' || start || end) ? 1 : 0);
}
