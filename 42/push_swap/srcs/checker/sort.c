/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 17:04:26 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/04 17:04:28 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		is_sorted(t_node *a)
{
	t_node *tmp;

	tmp = a;
	while (tmp)
	{
		if (a == tmp->next)
			break ;
		if (tmp->nb >= tmp->next->nb)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
