/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avideau <avideau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 14:58:50 by avideau           #+#    #+#             */
/*   Updated: 2016/11/30 13:00:48 by avideau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_list			*lstnew_tetris(char *buf, int i)
{
	t_list		*lstnew;
	t_map		map;
	int			n;

	map.y = 0;
	map.x = 0;
	n = 0;
	if (!(lstnew = (t_list*)malloc(sizeof(t_list))))
		return (0);
	lstnew->next = NULL;
	while (buf[n])
	{
		lstnew->matrice[map.y][map.x] = (buf[n] == '#') ? 1 : 0;
		map.x++;
		if (buf[n++] == '\n')
		{
			map.y++;
			map.x = 0;
		}
	}
	moveto_origin(lstnew->matrice);
	lstnew->h = get_height(lstnew->matrice);
	lstnew->w = get_width(lstnew->matrice);
	lstnew->letter[0] = i + 'A';
	return (lstnew);
}

int				lst_add(t_list **alst, t_list *new)
{
	t_list *lst;

	if (new == 0)
		return (0);
	if (*alst == NULL)
		*alst = new;
	else
	{
		lst = *alst;
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new;
		new = lst;
	}
	return (1);
}

void			ft_lstdel(t_list **alst)
{
	t_list *tmp;

	while (*alst)
	{
		tmp = (*alst)->next;
		free(*alst);
		*alst = tmp;
	}
	free(tmp);
	alst = NULL;
}
