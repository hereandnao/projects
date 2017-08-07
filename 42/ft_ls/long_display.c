/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 18:26:55 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/19 16:05:28 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			get_all_len(t_list *filelist, t_len *len)
{
	t_file	*file;
	int		tmp;

	ft_bzero(len, sizeof(t_len));
	while (filelist)
	{
		file = filelist->content;
		if ((tmp = ft_strlen(file->grp->gr_name)) >= len->len_group)
			len->len_group = tmp;
		if ((tmp = intsize(file->stat->st_nlink, 0)) >= len->len_links)
			len->len_links = tmp;
		if ((tmp = ft_strlen(file->pwd->pw_name)) >= len->len_owner_name)
			len->len_owner_name = tmp;
		if ((tmp = intsize(file->stat->st_size, 0)) >= len->len_fsize)
			len->len_fsize = tmp;
		filelist = filelist->next;
	}
}

static void		rights_end(t_file *file)
{
	if (file->rights[3] == 'x' && S_ISUID & file->stat->st_mode)
		file->rights[3] = 's';
	else if (S_ISUID & file->stat->st_mode)
		file->rights[3] = 'S';
	file->rights[4] = (S_IRGRP & file->stat->st_mode) ? 'r' : '-';
	file->rights[5] = (S_IWGRP & file->stat->st_mode) ? 'w' : '-';
	file->rights[6] = (S_IXGRP & file->stat->st_mode) ? 'x' : '-';
	if (file->rights[6] == 'x' && S_ISGID & file->stat->st_mode)
		file->rights[6] = 's';
	else if (S_ISGID & file->stat->st_mode)
		file->rights[6] = 'S';
	file->rights[7] = (S_IROTH & file->stat->st_mode) ? 'r' : '-';
	file->rights[8] = (S_IWOTH & file->stat->st_mode) ? 'w' : '-';
	file->rights[9] = (S_IXOTH & file->stat->st_mode) ? 'x' : '-';
	if (file->rights[9] == 'x' && S_ISVTX & file->stat->st_mode)
		file->rights[9] = 't';
	else if (S_ISVTX & file->stat->st_mode)
		file->rights[9] = 'T';
	file->rights[10] = '\0';
}

void			get_rights(t_file *file)
{
	if (S_ISREG(file->stat->st_mode) != 0)
		file->rights[0] = '-';
	else if (S_ISDIR(file->stat->st_mode))
		file->rights[0] = 'd';
	else if (S_ISLNK(file->stat->st_mode))
		file->rights[0] = 'l';
	else if (S_ISBLK(file->stat->st_mode))
		file->rights[0] = 'b';
	else if (S_ISCHR(file->stat->st_mode))
		file->rights[0] = 'c';
	else if (S_ISFIFO(file->stat->st_mode))
		file->rights[0] = 'i';
	file->rights[1] = (S_IRUSR & file->stat->st_mode) ? 'r' : '-';
	file->rights[2] = (S_IWUSR & file->stat->st_mode) ? 'w' : '-';
	file->rights[3] = (S_IXUSR & file->stat->st_mode) ? 'x' : '-';
	rights_end(file);
}
