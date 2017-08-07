/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 14:06:46 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/25 14:06:49 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *current;
	t_list *tmp;

	current = *alst;
	while (current)
	{
		del(current->content, current->content_size);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	*alst = NULL;
}
