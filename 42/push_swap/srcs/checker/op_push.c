/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 16:56:49 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/04 16:56:51 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/*
** pa : push a - take the first element at the top of b and put it at the top
** of a.
** Do nothing if b is empty.
**
** pb : push b - take the first element at the top of a and put it at the top
** of b.
** Do nothing if a is empty.
*/

void	pa(t_piles *p)
{
	if (!(p->b))
		return ;
	push_front(&p->a, p->b->nb);
	del_node(&p->b);
}

void	pb(t_piles *p)
{
	if (!(p->a))
		return ;
	push_front(&p->b, p->a->nb);
	del_node(&p->a);
}
