/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rationalize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 17:34:29 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/04 17:34:57 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

static int	size_cmp(void *a, void *b)
{
	if (((t_node *)a)->nb > ((t_node *)b)->nb)
		return (1);
	return (0);
}

int			rationalize(t_node *n, int size)
{
	int		i;
	t_node	**t;

	if (!(t = (t_node **)malloc(size * sizeof(t_node *))))
		return (0);
	i = 0;
	while (i < size)
	{
		t[i++] = n;
		n = n->next;
	}
	if (!(ft_merge_tab((void ***)&t, size, &size_cmp)))
		return (0);
	i = 0;
	while (i < size)
	{
		t[i]->nb = i;
		i++;
	}
	free(t);
	return (1);
}
