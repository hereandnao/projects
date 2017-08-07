/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:11:43 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/02 14:11:46 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int				count_nb(char *content)
{
	int i;
	int j;
	int nb;

	nb = 0;
	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] != ' ')
		{
			if (j == 0)
				nb++;
			j = 1;
		}
		else
			j = 0;
		i++;
	}
	return (nb);
}
