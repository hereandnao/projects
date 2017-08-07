/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_rev.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 16:57:01 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/04 16:57:03 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** ra : rotate a - shift up all elements of stack a by 1. The first element
** becomes
** the last one.
**
** rb : rotate b - shift up all elements of stack b by 1. The first element
** becomes
** the last one.
**
** rr : ra and rb at the same time.
*/

int		ra(t_piles *p, int do_write)
{
	if (!(p->a))
		return (1);
	p->a = p->a->next;
	if (do_write)
		ft_printf("ra\n");
	return (1);
}

int		rb(t_piles *p, int do_write)
{
	if (!(p->b))
		return (1);
	p->b = p->b->next;
	if (do_write)
		ft_printf("rb\n");
	return (1);
}

int		rr(t_piles *p, int do_write)
{
	ra(p, FALSE);
	rb(p, FALSE);
	if (do_write)
		ft_printf("rr\n");
	return (1);
}
