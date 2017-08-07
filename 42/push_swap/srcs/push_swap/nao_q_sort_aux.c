/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nao_q_sort_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 16:34:36 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/06 16:34:39 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				l_choose_pivot(int pivot, int size, int ratio)
{
	int i;

	i = pivot + ((size - pivot) / ratio);
	return (pivot = (pivot == i) ? pivot + 1 : i);
}

int				l_below_than_piv(t_node *a, int pivot)
{
	t_node		*tmp;
	int			i;

	tmp = a;
	i = 0;
	while (TRUE)
	{
		if (tmp->nb < pivot)
			i++;
		tmp = tmp->next;
		if (tmp == a)
			break ;
	}
	return (i);
}

static int		l_lower_or_higher(t_node *b, int n)
{
	int			i;

	if (!b || (b == b->next))
		return (-1);
	i = 0;
	while (b->nb != n)
	{
		i++;
		b = b->next;
	}
	return ((i < (n - i + 1)) ? 1 : 0);
}

void			l_move_to_higher(t_piles *p, t_env *e, int max, int do_write)
{
	e->trigger = FALSE;
	if ((l_lower_or_higher(p->b, max)) == 1)
		while (p->b->nb != max)
		{
			if (p->b->nb == (max - 1))
			{
				e->trigger = TRUE;
				e->b_length += pa(p, do_write);
			}
			if (p->b->nb == max)
				break ;
			e->b_length += rb(p, do_write);
		}
	else
		while (p->b->nb != max)
		{
			if (p->b->nb == (max - 1) && (p->b->prev->nb != max))
			{
				e->trigger = TRUE;
				e->b_length += pa(p, do_write);
			}
			if (p->b->nb == max)
				break ;
			e->b_length += rrb(p, do_write);
		}
}
