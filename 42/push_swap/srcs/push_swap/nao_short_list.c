/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nao_short_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 22:11:25 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/06 22:11:28 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		get_direction(t_node *n, int value)
{
	t_node		*tmp;
	int			i;
	int			j;

	if (n->nb == value)
		return (0);
	i = 0;
	j = 0;
	tmp = n;
	while (TRUE)
	{
		i++;
		if ((tmp = tmp->next)->nb == value)
			break ;
	}
	tmp = n;
	while (TRUE)
	{
		j++;
		if ((tmp = tmp->prev)->nb == value)
			break ;
	}
	return (i < (-1 * j) ? i : -j);
}

static void		move_pile(t_piles *p, int to_write, int *i)
{
	int direction;

	direction = get_direction(p->a, 0);
	while (direction)
	{
		i += (direction > 0) ? ra(p, to_write) : rra(p, to_write);
		direction -= (direction > 0) ? 1 : -1;
	}
}

static int		is_almost_sorted(t_piles *p, int max)
{
	t_node *a;

	a = p->a;
	while (TRUE)
	{
		if (a->nb > a->next->nb && !(a->nb == max && a->next->nb == 0))
			break ;
		a = a->next;
		if (a == p->a)
		{
			return (1);
		}
	}
	return (0);
}

unsigned int	short_rra(t_piles *p, int size, int to_write)
{
	int i;

	size--;
	i = 0;
	if (is_sorted(p->a) == 1)
		return (i);
	while (is_sorted(p->a) != 1)
	{
		if ((p->a->next->nb < p->a->nb) && !(p->a->nb == size
														&& p->a->next->nb == 0))
			sa(p, to_write);
		else
			rra(p, to_write);
		i++;
		if (is_almost_sorted(p, size))
			move_pile(p, to_write, &i);
	}
	return (i);
}

unsigned int	short_ra(t_piles *p, int size, int to_write)
{
	int i;

	size--;
	i = 0;
	if (is_sorted(p->a) == 1)
		return (i);
	while (is_sorted(p->a) != 1)
	{
		if ((p->a->next->nb < p->a->nb) && !(p->a->nb == size
														&& p->a->next->nb == 0))
			sa(p, to_write);
		else
			ra(p, to_write);
		i++;
		if (is_almost_sorted(p, size))
			move_pile(p, to_write, &i);
	}
	return (i);
}
