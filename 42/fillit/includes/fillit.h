/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avideau <avideau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 14:48:28 by avideau           #+#    #+#             */
/*   Updated: 2016/11/30 12:43:13 by avideau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct		s_list
{
	int				matrice[4][4];
	int				h;
	int				w;
	char			letter[1];
	struct s_list	*next;
}					t_list;

typedef struct		s_map
{
	int x;
	int y;
}					t_map;

typedef struct		s_read
{
	int			fd;
	int			ret;
	char		buf[21];
}					t_read;

t_list				*lstnew_tetris(char *buf, int i);
t_list				*readmap(char *file);
void				moveto_origin(int matrice[4][4]);
void				print_matrice(char **matrice, int size);
void				movecount(int *x, int *y, int size);
void				ft_putstr(char const *s);
void				ft_lstdel(t_list **alst);
void				ft_putchar(char c);
void				place_tetris(t_list *lst, char **map_tmp, t_map map);
void				replace_tetris(t_list *lst, char **map_tmp, t_map map);
void				free_matrice(char **result, int size);
void				place(char **map_tmp, int y, int x, char c);
char				**new_matrice(int size);
int					ft_strlen(const char *s);
int					lst_add(t_list **alst, t_list *new);
int					lst_size(t_list *begin_list);
int					calcul_min_size(int nb);
int					check_map(char *buf);
int					check_tetris(char *buf);
int					check_conditions(char *buf, int i);
int					getmin_col(int matrice[4][4]);
int					get_width(int matrice[4][4]);
int					get_height(int matrice[4][4]);
int					find_tetris(t_list *lst, char **map_tmp, t_map map);
int					tetris_solve(int map_size, char **map_tmp, t_list *lst);
int					check_tet_connex(char *buf);
int					check_point(char **tmp, int y, int x);
char				**test_pose(t_list *lst, int *size);
#endif
