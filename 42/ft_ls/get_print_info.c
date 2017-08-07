/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_print_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:35:20 by saubenne          #+#    #+#             */
/*   Updated: 2017/03/24 17:36:40 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		get_total(t_list *filelist)
{
	int		total;
	t_file	*tmp;
	t_list	*origin;

	total = 0;
	origin = filelist;
	if (filelist)
		tmp = filelist->content;
	while (filelist != NULL)
	{
		tmp = filelist->content;
		total += (int)tmp->stat->st_blocks;
		filelist = filelist->next;
	}
	if (origin)
		ft_printf("total %i\n", total);
	return (total);
}

char	*get_time(time_t file_time)
{
	time_t	now;
	char	*ftime;
	char	*res;

	res = NULL;
	now = time(0);
	ftime = ctime(&file_time);
	if (((now - file_time) >= 15778800) || (file_time > now))
		if (ft_strcmp(&ftime[23], " 10000\n") == 0)
			res = get_strtime(ftime, 23, 6);
		else
			res = get_strtime(ftime, 19, 5);
	else
		res = ft_fstrsub(ftime, 4, 12);
	return (res);
}

char	*get_strtime(char *dtime, int a, int b)
{
	char	*ntime;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strsub(dtime, 4, 7);
	tmp2 = ft_strsub(dtime, a, b);
	ntime = ft_strjoin(tmp, tmp2);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	return (ntime);
}
