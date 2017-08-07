/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 13:08:40 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/22 13:08:43 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_room	*create_room(char *str, int *coord)
{
	t_room	*new;
	int		i;

	i = 0;
	if (!(new = (t_room *)ft_memalloc(sizeof(t_room))))
		return (NULL);
	while (str[i] != ' ')
		i++;
	if (!(new->name = (char *)malloc((1 + i) * sizeof(char))))
		return (NULL);
	i = 0;
	while (str[i] != ' ')
	{
		new->name[i] = str[i];
		i++;
	}
	new->name[i] = '\0';
	new->x = coord[0];
	new->y = coord[1];
	new->n = -1;
	new->next = NULL;
	return (new);
}

static int		count_spaces(char *str)
{
	int count;

	count = 0;
	while (*str)
	{
		if (*str == '\t')
			return (1);
		if (*str == ' ')
			count++;
		str++;
	}
	return ((count == 2) ? 0 : 1);
}

static int		count_nb(char *str, int *tab)
{
	int count;
	int c;
	int err;

	c = 0;
	count = 0;
	err = FALSE;
	while (*str && !err)
	{
		if (*str != ' ' && *str != '\t' && c == 0)
		{
			if (count++ == 3)
				return (1);
			if (count > 1)
				*tab++ = ft_special_secure_atoi(str, &err);
			c = 1;
		}
		else if (*str == ' ' || *str == '\t')
			c = 0;
		str++;
	}
	return (count == 3 && !err) ? 0 : 1;
}

int				push_room(t_room **begin, char *str, t_map *map)
{
	t_room		*new;
	int			coord[2];

	if ((count_spaces(str) == 1) || (count_nb(str, coord) == 1))
		return (1);
	if (!(check_coord(coord, *begin, map)))
		return (1);
	if (!(new = create_room(str, coord)))
		exit(EXIT_FAILURE);
	if (!(*begin))
	{
		new->next = NULL;
		*begin = new;
	}
	else
	{
		new->next = (*begin);
		*begin = new;
	}
	return (0);
}

void			delete_room(t_room **rooms)
{
	t_room	*next;

	if (!(*rooms))
		return ;
	next = (*rooms)->next;
	free((*rooms)->name);
	free(*rooms);
	*rooms = next;
}
