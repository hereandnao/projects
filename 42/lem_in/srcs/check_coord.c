/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_coord.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 18:24:47 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/24 13:40:20 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		check_coord(int coord[2], t_room *p, t_map *map)
{
	while (p)
	{
		if (p->x == coord[0] && p->y == coord[1])
		{
			if (map->flags & VERBOSE)
				ft_printf("{red}Coords %i:%i already assigned{eoc}\n",
					coord[0], coord[1]);
			return (0);
		}
		p = p->next;
	}
	return (1);
}
