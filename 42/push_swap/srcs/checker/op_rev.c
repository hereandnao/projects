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

#include "checker.h"

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

void	ra(t_piles *p)
{
	if (!(p->a))
		return ;
	p->a = p->a->next;
}

void	rb(t_piles *p)
{
	if (!(p->b))
		return ;
	p->b = p->b->next;
}

void	rr(t_piles *p)
{
	ra(p);
	rb(p);
}
