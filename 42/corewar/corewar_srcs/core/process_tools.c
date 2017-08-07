/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <saubenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 15:57:48 by saubenne          #+#    #+#             */
/*   Updated: 2017/07/14 13:52:52 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "vm.h"

static void			delete_process(t_process **lst, t_process **current,
															t_process *prev)
{
	t_process		*tmp;

	tmp = *current;
	if (prev)
	{
		prev->next = (*current)->next;
		*current = prev->next;
	}
	else
	{
		*lst = (*current)->next;
		*current = *lst;
	}
	free(tmp);
}

/*
** int return -> Retourne le nombre de live
*/

int					destroy_process(t_process **lst)
{
	int				nb_lives;
	t_process		*current;
	t_process		*prev;

	prev = NULL;
	current = *lst;
	nb_lives = 0;
	while (current)
	{
		if (current->live == 0 && current->protection == FALSE)
		{
			delete_process(lst, &current, prev);
			continue;
		}
		nb_lives += current->live;
		current->live = 0;
		current->protection = FALSE;
		prev = current;
		current = current->next;
	}
	return (nb_lives);
}

int					free_all_process(t_process **lst)
{
	t_process		*current;
	t_process		*prev;

	prev = NULL;
	current = *lst;
	while (current)
		delete_process(lst, &current, prev);
	return (0);
}

void				create_process(t_warrior *warrior, int pc, t_process **lst,
																	t_env *e)
{
	t_process		*new;

	if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		exit(EXIT_FAILURE);
	new->owner = warrior;
	new->reg[0] = warrior->number;
	new->pc = pc;
	++e->nb_process;
	new->nb = e->nb_process;
	new->next = (!lst) ? NULL : *lst;
	*lst = new;
}

void				clone_process(t_process **lst, t_process *process, t_env *e)
{
	t_process		*new;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		exit(EXIT_FAILURE);
	ft_memcpy(new, process, sizeof(t_process));
	new->fn = NULL;
	new->live = 0;
	++e->nb_process;
	new->nb = e->nb_process;
	if (process->live)
		new->protection = TRUE;
	new->next = (!lst) ? NULL : *lst;
	*lst = new;
}
