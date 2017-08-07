/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 11:13:55 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/23 14:15:02 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"
# include <limits.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*
** x et y = coordoonnes de la salle
*/

typedef struct		s_room
{
	int				x;
	int				y;
	int				n;
	char			*name;
	struct s_room	*next;
	t_list			*tube;
}					t_room;

typedef enum		e_opts
{
	READ_FILE = 0x02,
	VERBOSE = 0x01
}					t_opts;

typedef struct		s_map
{
	struct s_room	*start;
	struct s_room	*end;
	int				nb_ants;
	t_opts			flags;
}					t_map;

typedef struct		s_pile
{
	t_room			*pile;
	struct s_pile	*next;
}					t_pile;

typedef struct		s_ant
{
	int				nb;
	t_pile			*loc;
}					t_ant;

int					count_ants(int fd, t_map *map);
int					get_next_line(const int fd, char **line);
int					push_room(t_room **begin, char *str, t_map *map);
void				delete_room(t_room **rooms);
int					check_coord(int coord[2], t_room *p, t_map *map);
int					add_room(t_map *map, t_room **rooms, char *line, int *err);
int					get_link(char *str, t_room *rooms);
int					syntax_valid(char *str, int *err);
int					ft_special_secure_atoi(const char *nptr, int *error);
t_pile				*a_star(t_map *map);
void				go_moving(t_pile *p, int n);
int					get_nao(int argc, char **argv, t_map *map);
void				debug_rooms(t_room *room, int n);
void				debug_path(t_pile *path);
void				debug_map_end(t_map *map);

#endif
