/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_rrev.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 16:57:14 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/04 16:57:15 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** rra : reverse rotate a - shift up all elements of stack a by 1.
** The last element becomes the first one.
**
** rrb : reverse rotate b - shift up all elements of stack b by 1.
** The last element becomes the first one.
**
** rrr : rra and rrb at the same time.
*/

int		rra(t_piles *p, int do_write)
{
	if (!(p->a))
		return (1);
	p->a = p->a->prev;
	if (do_write)
		ft_printf("rra\n");
	return (1);
}

int		rrb(t_piles *p, int do_write)
{
	if (!(p->b))
		return (1);
	p->b = p->b->prev;
	if (do_write)
		ft_printf("rrb\n");
	return (1);
}

int		rrr(t_piles *p, int do_write)
{
	rra(p, FALSE);
	rrb(p, FALSE);
	if (do_write)
		ft_printf("rrr\n");
	return (1);
}
