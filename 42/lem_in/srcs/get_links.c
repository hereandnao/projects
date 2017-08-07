/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 13:00:55 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/22 13:00:58 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				syntax_valid(char *str, int *err)
{
	int i;
	int count;

	if (*str == '#')
		return (0);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			*err = TRUE;
		if (str[i] == '-')
			count++;
		i++;
	}
	if (count != 1)
		*err = TRUE;
	return (0);
}

static int		custom_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '-')
		i++;
	if (s1[i] == '\0' && s2[i] == '-')
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static t_list	*l_new(void *content, size_t content_size)
{
	t_list *new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		exit(EXIT_FAILURE);
	new->content_size = content_size;
	new->content = content;
	new->next = NULL;
	return (new);
}

static void		create_link(t_room *a, t_room *b)
{
	t_list *new;

	new = l_new(b, sizeof(t_room *));
	if (!a->tube)
		a->tube = new;
	else
	{
		new->next = a->tube;
		a->tube = new;
	}
	new = l_new(a, sizeof(t_room *));
	if (!b->tube)
		b->tube = new;
	else
	{
		new->next = b->tube;
		b->tube = new;
	}
}

int				get_link(char *str, t_room *rooms)
{
	int		i;
	t_room	*room2;

	room2 = rooms;
	i = 0;
	while (rooms)
		if (custom_strcmp(rooms->name, str) != 0)
			rooms = rooms->next;
		else
			break ;
	while (str && str[i] != '-')
		i++;
	str = str + i + 1;
	while (room2 != NULL)
		if (custom_strcmp(room2->name, str) != 0)
			room2 = room2->next;
		else
			break ;
	if (!rooms || !room2 || rooms->name == room2->name)
		return (1);
	create_link(rooms, room2);
	return (0);
}
