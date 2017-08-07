/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <saubenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:09:42 by saubenne          #+#    #+#             */
/*   Updated: 2016/11/30 12:54:38 by avideau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void			place_tetris(t_list *lst, char **map_tmp, t_map map)
{
	t_map count;

	count.y = 0;
	count.x = 0;
	while (count.y != lst->w)
	{
		if (lst->matrice[count.x][count.y] == 1)
			place(map_tmp, map.x + count.y, map.y + count.x, lst->letter[0]);
		movecount(&count.x, &count.y, lst->h);
	}
}

void			replace_tetris(t_list *lst, char **map_tmp, t_map map)
{
	t_map count;

	count.y = 0;
	count.x = 0;
	while (count.y != lst->w)
	{
		if (lst->matrice[count.x][count.y] == 1)
			place(map_tmp, map.x + count.y, map.y + count.x, '.');
		movecount(&count.x, &count.y, lst->h);
	}
}

int				find_tetris(t_list *lst, char **tmp, t_map map)
{
	t_map	count;
	int		cal_x;
	int		cal_y;

	count.y = 0;
	count.x = 0;
	while (count.y != lst->w)
	{
		cal_y = map.x + count.y;
		cal_x = map.y + count.x;
		if (lst->matrice[count.x][count.y] == 1 &&
				check_point(tmp, cal_y, cal_x))
			return (0);
		movecount(&count.x, &count.y, lst->h);
	}
	place_tetris(lst, tmp, map);
	return (1);
}

int				check_point(char **tmp, int y, int x)
{
	return ((tmp[y][x] == '.') ? 0 : 1);
}

void			place(char **map_tmp, int y, int x, char c)
{
	map_tmp[y][x] = c;
}
