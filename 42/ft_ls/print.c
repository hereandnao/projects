/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 14:12:11 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/25 14:12:16 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		begin(t_len *len, t_list **filelist, int no_total,
																t_opts *flags)
{
	if (*flags & S_REVERSE)
		ft_listinvert(filelist);
	if (*flags & INFOS)
	{
		get_all_len(*filelist, len);
		if (!no_total)
			get_total(*filelist);
	}
}

static void		print_infos(t_file *tmp, t_len *len)
{
	char		*tm;

	ft_printf("%s  %*d %-*s  %-*s  ", tmp->rights, len->len_links,
		(int)tmp->stat->st_nlink, len->len_owner_name, tmp->pwd->pw_name,
		len->len_group, tmp->grp->gr_name);
	if (tmp->rights[0] != 'c')
		ft_printf("%*lld ", len->len_fsize,
									(long long int)tmp->stat->st_size);
	else
		ft_printf("%4ld, %4ld ", (long int)major(tmp->stat->st_rdev),
								(long int)minor(tmp->stat->st_rdev));
	tm = get_time(tmp->stat->st_mtime);
	ft_printf("%s ", tm);
	free(tm);
}

static t_list	*pr(t_len *len, t_list **filelist, int no_total, t_opts *flags)
{
	begin(len, filelist, no_total, flags);
	return (*filelist);
}

void			print_list(t_list **filelist, t_opts *flags, int no_total)
{
	t_file	*tmp;
	t_len	len;
	char	link_buf[LINK_SIZE];
	int		i;
	t_list	*tmp_list;

	tmp_list = pr(&len, filelist, no_total, flags);
	while (tmp_list != NULL)
	{
		tmp = tmp_list->content;
		(*flags & INFOS) ? print_infos(tmp, &len) : NULL;
		ft_printf("%s", tmp->name);
		if (tmp->rights[0] == 'l' && (*flags & INFOS))
		{
			if ((i = readlink(tmp->pathname, link_buf, LINK_SIZE)) < 0)
				err_printf(NONE_LS" %s: %s", tmp->name, strerror(errno));
			else
			{
				link_buf[i] = '\0';
				ft_printf(" -> %s", link_buf);
			}
		}
		ft_printf("\n");
		tmp_list = tmp_list->next;
	}
}
