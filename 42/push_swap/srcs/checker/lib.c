/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 17:04:19 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/04 17:04:21 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "checker.h"

static t_node	*create_node(int nb)
{
	t_node *new;

	if (!(new = malloc(sizeof(t_node))))
		return (NULL);
	new->nb = nb;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void			push_front(t_node **lstnode, int nb)
{
	t_node *new;

	if (!(new = create_node(nb)))
		exit(EXIT_FAILURE);
	if (!(*lstnode))
	{
		new->prev = new;
		new->next = new;
	}
	else
	{
		new->next = *lstnode;
		new->prev = (*lstnode)->prev;
		(*lstnode)->prev = new;
		new->prev->next = new;
	}
	*lstnode = new;
}

void			push_back(t_node **begin, int nb)
{
	t_node		*new;

	if (!(new = create_node(nb)))
		exit(EXIT_FAILURE);
	if (!(*begin))
	{
		new->prev = new;
		new->next = new;
		*begin = new;
	}
	else
	{
		new->prev = (*begin)->prev;
		new->next = (*begin);
		(*begin)->prev->next = new;
		(*begin)->prev = new;
	}
}

void			del_node(t_node **node)
{
	t_node	*tmp;

	tmp = *node;
	if (*node == NULL)
		return ;
	(*node)->prev->next = (*node)->next;
	(*node)->next->prev = (*node)->prev;
	if ((*node)->next == *node)
		*node = NULL;
	else
		*node = (*node)->next;
	free(tmp);
}
