/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinvert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 17:33:33 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/26 01:14:20 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*invert(t_list **alst, t_list *ptr)
{
	if (!ptr->next)
		*alst = ptr;
	else
		invert(alst, ptr->next)->next = ptr;
	return (ptr);
}

t_list			*ft_lst_invert_rec(t_list **alst)
{
	invert(alst, *alst)->next = NULL;
	return (*alst);
}
