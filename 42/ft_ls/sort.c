/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 14:12:29 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/25 14:12:33 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			sort(t_list *lst, t_opts *flags)
{
	if (lst == NULL)
		return ;
	sort_list(lst);
	if (*flags & S_BY_DATE)
		sort_by_time(lst);
	else if (*flags & S_BY_SIZE)
		sort_by_size(lst);
}

static int		alpha_cmp(t_list *t)
{
	char *s1;
	char *s2;

	s1 = ((t_file *)t->content)->name;
	s2 = ((t_file *)t->next->content)->name;
	return ((ft_strcmp(s1, s2) <= 0) ? 0 : 1);
}

static void		swap_content(t_list *t)
{
	void *tmp;

	tmp = t->content;
	t->content = t->next->content;
	t->next->content = tmp;
}

void			sort_list(t_list *filelist)
{
	int		ret;
	t_list	*origin;

	origin = filelist;
	ret = 1;
	while (ret != 0)
	{
		ret = 0;
		filelist = origin;
		while (filelist->next != NULL)
		{
			ret += alpha_cmp(filelist);
			if (alpha_cmp(filelist) != 0)
				swap_content(filelist);
			filelist = filelist->next;
		}
	}
}
