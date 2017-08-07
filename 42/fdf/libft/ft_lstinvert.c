/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinvert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:50:52 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/19 22:50:54 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstinvert(t_list **alst)
{
	t_list *p;
	t_list *c;
	t_list *n;

	p = NULL;
	c = *alst;
	while (c)
	{
		n = c->next;
		c->next = p;
		p = c;
		c = n;
	}
	*alst = p;
	return (*alst);
}
