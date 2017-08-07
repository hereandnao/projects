/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 14:11:48 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/25 14:11:49 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		del(void *chain, size_t i)
{
	t_file *file;

	file = (t_file *)chain;
	if (i)
	{
	}
	free(file->name);
	free(file->pathname);
	free(file->stat);
	free(chain);
}

static void		del_dir(void *chain, size_t i)
{
	(void)chain;
	(void)i;
}

static void		end_proc(t_lst_duo *t, t_opts *flags, int n, int z)
{
	t_list			*tmp;

	if (t->lst_file)
		sort(t->lst_file, flags);
	if (t->lst_dir)
		sort(t->lst_dir, flags);
	if (t->lst_dir && (*flags & S_REVERSE))
		ft_listinvert(&(t->lst_dir));
	print_list(&(t->lst_file), flags, 0);
	tmp = t->lst_dir;
	while (tmp)
	{
		recurse(((t_file *)tmp->content)->pathname, flags, n + 1, z);
		tmp = tmp->next;
	}
	ft_lstdel(&(t->lst_file), &del);
	ft_lstdel(&(t->lst_dir), &del_dir);
}

static void		proceed(t_lst_duo *t, DIR *stream, t_opts *flags, char *nao)
{
	t_file			*file;
	struct dirent	*naodir;

	while ((naodir = readdir(stream)))
	{
		if (naodir->d_name[0] == '.' && (!(*flags & MASKED)))
			continue;
		file = (t_file *)malloc(sizeof(t_file));
		file->pathname = ft_strjoin(nao, naodir->d_name);
		file->name = ft_strdup(naodir->d_name);
		fill_strct(file, naodir, flags);
		if (S_ISDIR(file->stat->st_mode))
		{
			if (ft_strcmp(file->name, "..") != 0 &&
											ft_strcmp(file->name, ".") != 0)
				ft_push_front(&(t->lst_dir), file, sizeof(t_file *));
		}
		ft_push_front(&(t->lst_file), file, sizeof(t_file *));
	}
}

void			recurse(char *dir_name, t_opts *flags, int n, int z)
{
	DIR				*stream;
	t_lst_duo		t;
	char			*nao;

	nao = dir_name;
	ft_bzero(&t, sizeof(t_lst_duo));
	add_line(n, z, flags, dir_name);
	if (!(stream = opendir(dir_name)))
	{
		err_printf("./ft_ls: %s: %s\n", dir_name, strerror(errno));
		return ;
	}
	if (dir_name[ft_strlen(dir_name) - 1] != '/')
		nao = ft_strjoin(nao, "/");
	proceed(&t, stream, flags, nao);
	end_proc(&t, flags, n, z);
	if (closedir(stream))
	{
		err_printf("Could not close '%s': %s\n", dir_name, strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (dir_name[ft_strlen(dir_name) - 1] != '/')
		free(nao);
}
