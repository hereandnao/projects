/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:33:55 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/25 14:13:43 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	fill_strct(t_file *file, struct dirent *dir, t_opts *flags)
{
	char *tmp;

	if (!(*flags & RECURSE))
	{
		if (!(file->name = ft_strdup(dir->d_name)))
			exit(EXIT_FAILURE);
		if (!(tmp = ft_strjoin(file->path, "/")))
			exit(EXIT_FAILURE);
		if (!(file->pathname = ft_strjoin(tmp, file->name)))
			exit(EXIT_FAILURE);
		free(tmp);
	}
	if (!(file->stat = malloc(sizeof(struct stat))))
		exit(EXIT_FAILURE);
	lstat(file->pathname, file->stat);
	file->grp = getgrgid(file->stat->st_gid);
	file->pwd = getpwuid(file->stat->st_uid);
	get_rights(file);
}
