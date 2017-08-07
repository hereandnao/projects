/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <saubenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 13:10:11 by saubenne          #+#    #+#             */
/*   Updated: 2016/11/30 12:54:50 by avideau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			calcul_min_size(int nb)
{
	int size;

	size = 2;
	while (size * size < nb)
		size++;
	size = size * 2;
	return (size - 2);
}

int			lst_size(t_list *begin_list)
{
	int i;

	i = 1;
	if (!begin_list)
		return (0);
	while (begin_list->next)
	{
		begin_list = begin_list->next;
		i = i + 1;
	}
	return (i);
}

int			tetris_solve(int map_size, char **map_tmp, t_list *lst)
{
	t_map count;

	count.x = 0;
	count.y = 0;
	while (count.y <= (map_size - lst->h))
	{
		if (count.x <= (map_size - lst->w))
		{
			if (find_tetris(lst, map_tmp, count))
			{
				if (lst->next == NULL ||
						tetris_solve(map_size, map_tmp, lst->next))
					return (1);
				else
					replace_tetris(lst, map_tmp, count);
			}
		}
		movecount(&count.x, &count.y, map_size);
	}
	return (0);
}
