/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 17:20:23 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/04 17:20:33 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

void		view_list(t_piles *p)
{
	t_node *tmp;

	tmp = p->a;
	ft_printf("{red}Pile A: {eoc}");
	while (tmp)
	{
		ft_printf("%d ", tmp->nb);
		tmp = tmp->next;
		if (p->a == tmp)
			break ;
	}
	tmp = p->b;
	ft_printf("\n{green}Pile B: {eoc}");
	while (tmp)
	{
		ft_printf("%d ", tmp->nb);
		tmp = tmp->next;
		if (p->b == tmp)
			break ;
	}
	ft_putchar('\n');
	ft_putchar('\n');
}

void		view_list_verb(t_piles *p)
{
	t_node *tmp;

	tmp = p->a;
	ft_printf("\n{green}Contenu de la pile A: {eoc}\n");
	while (tmp)
	{
		ft_printf("%d ", tmp->nb);
		tmp = tmp->next;
		if (p->a == tmp)
			break ;
	}
	ft_putchar('\n');
	ft_putchar('\n');
}

t_node		*clone_nodes(t_node *original)
{
	t_node *new;
	t_node *a;

	if (!original)
		return (NULL);
	new = NULL;
	a = original;
	while (TRUE)
	{
		if (!(push_back(&new, original->nb)))
			exit(EXIT_FAILURE);
		original = original->next;
		if (original == a)
			break ;
	}
	return (new);
}

int			is_sorted(t_node *a)
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
