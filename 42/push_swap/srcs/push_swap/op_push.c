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

#include "push_swap.h"

/*
** pa : push a - take the first element at the top of b and put it at the top
** of a.
** Do nothing if b is empty.
**
** pb : push b - take the first element at the top of a and put it at the top
** of b.
** Do nothing if a is empty.
*/

int		pa(t_piles *p, int do_write)
{
	if (!(p->b))
		return (1);
	push_front(&p->a, p->b->nb);
	del_node(&p->b);
	if (do_write)
		ft_printf("pa\n");
	return (1);
}

int		pb(t_piles *p, int do_write)
{
	if (!(p->a))
		return (1);
	push_front(&p->b, p->a->nb);
	del_node(&p->a);
	if (do_write)
		ft_printf("pb\n");
	return (1);
}
