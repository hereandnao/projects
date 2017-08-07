/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:25:01 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/21 12:06:52 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <inttypes.h>

typedef struct		s_len
{
	int				len_links;
	int				len_owner_name;
	int				len_group;
	int				len_fsize;
}					t_len;

typedef struct		s_file
{
	char			*name;
	char			*path;
	char			*pathname;
	char			rights[11];
	struct group	*grp;
	struct passwd	*pwd;
	struct stat		*stat;
	int				total;
}					t_file;

typedef struct		s_lst_duo
{
	t_list			*lst_dir;
	t_list			*lst_file;
}					t_lst_duo;

# define STDERR 	1
# define LINK_SIZE 	2048
# define NO_ACCESS	""
# define NONE_LS 	" -> ./ft_ls: Cannot open directory"

typedef enum		e_opts
{
	MULTI_DIR = 0x100,
	COLOR = 0x80,
	INFOS = 0x40,
	RECURSE = 0x20,
	MASKED = 0x10,
	UNSORTED = 0x08,
	S_BY_SIZE = 0x04,
	S_BY_DATE = 0x02,
	S_REVERSE = 0x01
}					t_opts;

void				parse(int argc, char **argv, t_lst_duo *t, t_opts *flags);
int					add_to_input(char *s, t_list **input_list);
void				ft_list_sort(t_list *begin_list, int (*cmp)());
int					assign_input(t_lst_duo *t, t_list *input_list, char *cmd);
void				add_line(int n, int z, t_opts *flags, char *dir_name);
void				no_recurse(t_list *dir_list, t_opts *flags, char *cmd);
void				recurse(char *dir_name, t_opts *flags, int n, int z);
void				sort_list(t_list *filelist);
void				print_list(t_list **filelist, t_opts *flags, int no_total);
void				sort_by_time(t_list *filelist);
void				sort_by_size(t_list *filelist);
void				get_all_len(t_list *filelist, t_len *len);
void				get_rights(t_file *file);
void				fill_strct(t_file *file, struct dirent *dir, t_opts *flags);
void				sort(t_list *lst, t_opts *flags);
int					ft_push_front(t_list **alst, void *data, size_t size);
int					get_total(t_list *filelist);
char				*get_time(time_t file_time);
char				*get_strtime(char *dtime, int a, int b);
void				ft_listinvert(t_list **alst);

#endif
