/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 14:12:40 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/25 14:12:43 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		swap_content(t_list *t)
{
	void *tmp;

	tmp = t->content;
	t->content = t->next->content;
	t->next->content = tmp;
}

static int		size_cmp(t_list *filelist)
{
	off_t size1;
	off_t size2;

	size1 = ((t_file *)filelist->content)->stat->st_size;
	size2 = ((t_file *)filelist->next->content)->stat->st_size;
	return ((size1 < size2) ? 1 : 0);
}

void			sort_by_size(t_list *filelist)
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
			ret += size_cmp(filelist);
			if (size_cmp(filelist) != 0)
				swap_content(filelist);
			filelist = filelist->next;
		}
	}
}

static int		time_cmp(t_list *filelist)
{
	time_t t1;
	time_t t2;

	t1 = ((t_file *)filelist->content)->stat->st_mtime;
	t2 = ((t_file *)filelist->next->content)->stat->st_mtime;
	return ((t1 < t2) ? 1 : 0);
}

void			sort_by_time(t_list *filelist)
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
			ret += time_cmp(filelist);
			if (time_cmp(filelist) != 0)
				swap_content(filelist);
			filelist = filelist->next;
		}
	}
}
