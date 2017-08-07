/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_recurse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:56:37 by saubenne          #+#    #+#             */
/*   Updated: 2017/03/24 17:57:34 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			del(void *chain, size_t i)
{
	t_file *file;

	file = (t_file *)chain;
	if (i)
	{
	}
	if (file->pathname)
		free(file->pathname);
	if (file->name)
		free(file->name);
	if (file->stat)
		free(file->stat);
	free(chain);
}

static void			assign(t_list *filelist, t_opts *flags, t_file *file,
																DIR *stream)
{
	sort(filelist, flags);
	print_list(&filelist, flags, 0);
	free(file->path);
	closedir(stream);
	ft_lstdel(&filelist, &del);
}

static void			multi_dir(int cond, t_file *content)
{
	(cond) ? ft_putchar('\n') : NULL;
	ft_printf("%s:\n", content->pathname);
}

static DIR			*get_stream(char *s, char *cmd)
{
	DIR				*stream;

	if (!(stream = opendir(s)))
	{
		err_printf("%s: %s: %s\n", cmd, s, strerror(errno));
		return (NULL);
	}
	return (stream);
}

void				no_recurse(t_list *dir_list, t_opts *flags, char *cmd)
{
	DIR				*stream;
	struct dirent	*ndir;
	t_file			file;
	t_list			*filelist;
	t_list			*origin;

	origin = dir_list;
	while (dir_list)
	{
		filelist = NULL;
		file.path = ft_strdup(((t_file *)dir_list->content)->pathname);
		if (*flags & MULTI_DIR)
			multi_dir((dir_list != origin) ? 1 : 0, dir_list->content);
		if (!(stream = get_stream(file.path, cmd)))
			return ;
		while ((ndir = readdir(stream)))
			if (ndir->d_name[0] != '.' || (*flags & MASKED))
			{
				fill_strct(&file, ndir, flags);
				ft_lstadd(&filelist, (ft_lstnew(&file, sizeof(file))));
			}
		assign(filelist, flags, &file, stream);
		dir_list = dir_list->next;
	}
}
