/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nao_q_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 18:09:31 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/05 06:37:53 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		l_sort_p_a(t_piles *p, t_env *e, int *size, int to_write)
{
	t_node		*tmp;

	while ((is_sorted(p->a)) != 1)
	{
		if (p->a->next->nb < p->a->nb)
			e->a_length += sa(p, to_write);
		else
			e->a_length += rra(p, to_write);
	}
	tmp = p->a;
	while (TRUE)
	{
		(*size)--;
		tmp = tmp->next;
		if (tmp == p->a)
			break ;
	}
}

static void		l_fill_p_a(t_piles *p, t_env *e, int max, int to_write)
{
	while (p->b != NULL)
	{
		l_move_to_higher(p, e, max, to_write);
		if (e->trigger)
		{
			e->b_length += pa(p, to_write);
			max -= 2;
			if (p->b->nb < p->b->next->nb)
				e->b_length += ss(p, to_write);
			else
				e->b_length += sa(p, to_write);
		}
		else
		{
			max--;
			e->b_length += pa(p, to_write);
		}
	}
}

unsigned int	nao_q_sort(t_piles *p, int size, int ratio, t_env *e)
{
	int pivot;
	int n_below_than_piv;

	pivot = 0;
	n_below_than_piv = 0;
	while (pivot < (size - 1) && (p->a->nb != p->a->next->next->nb))
	{
		if (n_below_than_piv == 0)
		{
			pivot = l_choose_pivot(pivot, size, ratio);
			n_below_than_piv = l_below_than_piv(p->a, pivot);
		}
		if (p->a->nb < pivot)
		{
			n_below_than_piv--;
			e->a_length += pb(p, e->to_write);
		}
		else
			e->a_length += ra(p, e->to_write);
	}
	l_sort_p_a(p, e, &size, e->to_write);
	l_fill_p_a(p, e, size - 1, e->to_write);
	e->f_length = e->a_length + e->b_length;
	return (e->f_length);
}
