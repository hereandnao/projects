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

#include "checker.h"

/*
** sa : swap a - swap the first two elements at the top of stack a.
** Do nothing if there is only one or no elements.
**
** sb : swap b - swap the first two elements at the top of stack b.
** Do nothing if there is only one or no elements.
**
** ss : sa and sb at the same time.
*/

void	sa(t_piles *p)
{
	int tmp;

	if (!(p->a))
		return ;
	tmp = p->a->nb;
	p->a->nb = p->a->next->nb;
	p->a->next->nb = tmp;
}

void	sb(t_piles *p)
{
	int tmp;

	if (!(p->b))
		return ;
	tmp = p->b->nb;
	p->b->nb = p->b->next->nb;
	p->b->next->nb = tmp;
}

void	ss(t_piles *p)
{
	sa(p);
	sb(p);
}
