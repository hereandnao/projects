/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 16:56:25 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/04 16:56:30 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** sa : swap a - swap the first two elements at the top of stack a.
** Do nothing if there is only one or no elements.
**
** sb : swap b - swap the first two elements at the top of stack b.
** Do nothing if there is only one or no elements.
**
** ss : sa and sb at the same time.
*/

int		sa(t_piles *p, int do_write)
{
	int tmp;

	if (!(p->a))
		return (1);
	tmp = p->a->nb;
	p->a->nb = p->a->next->nb;
	p->a->next->nb = tmp;
	if (do_write)
		ft_printf("sa\n");
	return (1);
}

int		sb(t_piles *p, int do_write)
{
	int tmp;

	if (!(p->b))
		return (1);
	tmp = p->b->nb;
	p->b->nb = p->b->next->nb;
	if (do_write)
		ft_printf("sb\n");
	p->b->next->nb = tmp;
	return (1);
}

int		ss(t_piles *p, int do_write)
{
	sa(p, FALSE);
	sb(p, FALSE);
	if (do_write)
		ft_printf("ss\n");
	return (1);
}
