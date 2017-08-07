/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 14:04:29 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/25 14:04:32 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_push_front(t_list **alst, void *data, size_t size)
{
	t_list *new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (-1);
	new->content = data;
	new->content_size = size;
	if (!*alst)
		new->next = NULL;
	else
		new->next = *alst;
	*alst = new;
	return (0);
}

int				ft_list_size(t_list *begin_list)
{
	int i;

	i = 1;
	if (!begin_list)
		return (0);
	while (begin_list->next)
	{
		begin_list = begin_list->next;
		i++;
	}
	return (i);
}

void			ft_listinvert(t_list **alst)
{
	t_list		*prev;
	t_list		*current;
	t_list		*next;

	prev = NULL;
	current = *alst;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*alst = prev;
}

void			add_line(int n, int z, t_opts *flags, char *dir_name)
{
	if (n != 0 || z)
		ft_printf("\n");
	if (n != 0 || (*flags & MULTI_DIR))
		ft_printf("%s:\n", dir_name);
}
