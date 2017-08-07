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

#include "checker.h"

/*
** rra : reverse rotate a - shift up all elements of stack a by 1.
** The last element becomes the first one.
**
** rrb : reverse rotate b - shift up all elements of stack b by 1.
** The last element becomes the first one.
**
** rrr : rra and rrb at the same time.
*/

void	rra(t_piles *p)
{
	if (!(p->a))
		return ;
	p->a = p->a->prev;
}

void	rrb(t_piles *p)
{
	if (!(p->b))
		return ;
	p->b = p->b->prev;
}

void	rrr(t_piles *p)
{
	rra(p);
	rrb(p);
}
