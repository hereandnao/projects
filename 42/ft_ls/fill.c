/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:41:59 by saubenne          #+#    #+#             */
/*   Updated: 2017/03/24 17:43:00 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int			fill(t_lst_duo *t, char *s, char *cmd)
{
	t_file			*entity;
	struct stat		*statistics;
	int				err;

	if (!(statistics = (struct stat *)malloc(sizeof(struct stat))))
		return (-1);
	if (lstat(s, statistics) == -1)
	{
		err_printf("%s:"NO_ACCESS" %s: %s\n", cmd, s, strerror(errno));
		return (0);
	}
	if (!(entity = (t_file *)malloc(sizeof(t_file))))
		return (-1);
	entity->stat = statistics;
	entity->pathname = ft_strdup(s);
	entity->name = entity->pathname;
	entity->grp = getgrgid(entity->stat->st_gid);
	entity->pwd = getpwuid(entity->stat->st_uid);
	get_rights(entity);
	if (S_ISDIR(entity->stat->st_mode))
		err = ft_push_front(&(t->lst_dir), entity, sizeof(t_file));
	else
		err = ft_push_front(&(t->lst_file), entity, sizeof(t_file));
	return ((err) ? -1 : 0);
}

int					add_to_input(char *s, t_list **input_list)
{
	ft_lstadd(input_list, (ft_lstnew(s, ft_strlen(s) + 1)));
	return (0);
}

void				ft_list_sort(t_list *begin_list, int (*cmp)())
{
	t_list	*ptr;
	int		trigger;
	void	*tmp;

	if (!begin_list || !(begin_list->next))
		return ;
	trigger = 1;
	while (trigger)
	{
		ptr = begin_list;
		trigger = 0;
		while (ptr->next)
		{
			if (cmp(ptr->content, ptr->next->content) > 0)
			{
				trigger = 1;
				tmp = ptr->next->content;
				ptr->next->content = ptr->content;
				ptr->content = tmp;
			}
			ptr = ptr->next;
		}
	}
}

static void			del(void *chain, size_t i)
{
	(void)i;
	free(chain);
}

int					assign_input(t_lst_duo *t, t_list *input_list, char *cmd)
{
	t_list *ptr;

	ptr = input_list;
	while (ptr)
	{
		if (fill(t, ptr->content, cmd))
			return (-1);
		ptr = ptr->next;
	}
	ft_lstdel(&input_list, &del);
	return (0);
}
