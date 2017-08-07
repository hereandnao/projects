/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 11:20:36 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/23 14:15:45 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Tant que add_room renvoit 1, on continue de l'acquisition des salles
*/

static void		free_all_memory(t_room *room, t_pile *path)
{
	t_room *room_next;
	t_pile *path_next;
	t_list *tube_next;

	while (room)
	{
		room_next = room->next;
		while (room->tube)
		{
			tube_next = room->tube->next;
			free(room->tube);
			room->tube = tube_next;
		}
		free(room->name);
		free(room);
		room = room_next;
	}
	while (path)
	{
		path_next = path->next;
		free(path);
		path = path_next;
	}
}

static int		parse_file(t_map *map, t_room **room, int fd)
{
	char	*line;
	int		err;
	int		t;

	t = 0;
	err = FALSE;
	while (get_next_line(fd, &line) > 0)
	{
		if (!t && (add_room(map, room, line, &err) == 0))
			t = 1;
		if (err == TRUE)
			return (1);
		if (t == 1 && (!(ft_strcmp("##end", line)) ||
											(!(ft_strcmp("##start", line)))))
			return (1);
		if (t == 1 && syntax_valid(line, &err))
			continue;
		if (err == TRUE)
			return (1);
		if (t == 1 && *line != '#' && get_link(line, *room))
			return (1);
		ft_printf("%s\n", line);
		free(line);
	}
	return (0);
}

static void		error_display(void)
{
	ft_printf("ERROR\n");
	exit(EXIT_FAILURE);
}

int				main(int argc, char **argv)
{
	t_map		map;
	int			fd;
	t_room		*room;
	t_pile		*path;

	ft_bzero(&map, sizeof(t_map));
	room = NULL;
	path = NULL;
	fd = get_nao(argc, argv, &map);
	if ((map.nb_ants = count_ants(fd, &map)) == -1)
		error_display();
	parse_file(&map, &room, fd);
	if (map.flags & VERBOSE)
		debug_rooms(room, map.nb_ants);
	if ((!(map.end)) || (!(map.start)) || (!(path = a_star(&map))))
		error_display();
	if (map.flags & VERBOSE)
		debug_path(path);
	go_moving(path, map.nb_ants);
	free_all_memory(room, path);
	return (0);
}
