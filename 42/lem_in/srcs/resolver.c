/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 13:11:14 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/22 13:11:16 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void			add_room_to_pile(t_room *room, t_pile **p)
{
	t_pile *new;

	if (!(new = (t_pile *)malloc(sizeof(t_pile))))
		exit(EXIT_FAILURE);
	if (*p == NULL)
		new->next = NULL;
	else
		new->next = *p;
	*p = new;
	new->pile = room;
}

static t_pile		*create_pile(t_pile *p, int nb)
{
	t_pile *new;
	t_pile *a;
	t_list *tmp;

	new = NULL;
	a = p;
	while (a != NULL)
	{
		a->pile->n = nb;
		a = a->next;
	}
	while (p != NULL)
	{
		tmp = p->pile->tube;
		while (tmp)
		{
			if (((t_room*)tmp->content)->n == -1)
				add_room_to_pile(tmp->content, &new);
			tmp = tmp->next;
		}
		p = p->next;
	}
	return (new);
}

static t_pile		*get_path(t_map *map)
{
	t_pile	*path;
	t_list	*tmp;
	t_room	*ptr;
	int		nb;

	path = NULL;
	ptr = map->end;
	nb = map->end->n;
	add_room_to_pile(map->end, &path);
	while (nb > 0)
	{
		tmp = ptr->tube;
		while (((t_room *)tmp->content)->n != nb - 1)
			tmp = tmp->next;
		ptr = tmp->content;
		add_room_to_pile(ptr, &path);
		nb--;
	}
	return (path);
}

static void			fflush_pile(t_pile *p)
{
	t_pile *p_next;

	while (p)
	{
		p_next = p->next;
		free(p);
		p = p_next;
	}
}

t_pile				*a_star(t_map *map)
{
	t_pile	*p;
	t_pile	*n;
	int		nb;

	n = NULL;
	nb = 0;
	add_room_to_pile(map->start, &n);
	while ((p = create_pile(n, nb++)) != NULL)
	{
		fflush_pile(n);
		n = p;
	}
	fflush_pile(n);
	if (map->flags & VERBOSE)
		debug_map_end(map);
	if (map->end->n == -1)
		return (NULL);
	return (get_path(map));
}
