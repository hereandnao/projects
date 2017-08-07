/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 13:58:12 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/24 13:39:37 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	debug_rooms(t_room *room, int n)
{
	t_list *tmp;

	ft_printf("\nDEBUG ROOMS:\n");
	ft_printf("------------\n");
	ft_printf("{green}Nb of ants : %i{eoc}\n", n);
	while (room)
	{
		ft_printf("{red}ROOM %-40s{eoc} -> %p\n", ((t_room *)room)->name,
														((t_room *)room)->tube);
		tmp = room->tube;
		while (tmp)
		{
			ft_printf("{yellow}link %-40s{eoc} -> %p\n",
								((t_room *)tmp->content)->name, tmp->content);
			tmp = tmp->next;
		}
		room = room->next;
	}
	ft_printf("\n");
}

void	debug_path(t_pile *path)
{
	ft_printf("DEBUG PATH:\n");
	ft_printf("-----------\n");
	while (path)
	{
		ft_printf("Path = {green}%s{eoc}\n", path->pile->name);
		path = path->next;
	}
	ft_printf("\n");
}

void	debug_map_end(t_map *map)
{
	ft_printf("DEBUG MAP END:\n");
	ft_printf("--------------\n");
	ft_printf("map end nb = %d\n\n", map->end->n);
}
