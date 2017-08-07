/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 14:11:42 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/25 14:11:43 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		assign_flags(t_opts *flags, char *s)
{
	while (*s)
	{
		if (*s == 'G')
			*flags |= COLOR;
		else if (*s == 'l')
			*flags |= INFOS;
		else if (*s == 'R')
			*flags |= RECURSE;
		else if (*s == 'a')
			*flags |= MASKED;
		else if (*s == 'f')
			*flags |= UNSORTED;
		else if (*s == 'S')
			*flags |= S_BY_SIZE;
		else if (*s == 't')
			*flags |= S_BY_DATE;
		else if (*s == 'r')
			*flags |= S_REVERSE;
		else if (*s == '1')
			*flags = *flags;
		else
			return (*s);
		s++;
	}
	return (0x00);
}

static void		del(void *chain, size_t i)
{
	t_file *file;

	(void)i;
	file = (t_file *)chain;
	free(file->stat);
	free(file->name);
	free(chain);
}

static void		error_msg(char *cmd, char letter)
{
	ft_putstr_fd(cmd, STDERR);
	ft_putstr_fd(": illegal option -- ", STDERR);
	ft_putchar_fd(letter, STDERR);
	ft_putstr_fd("\nusage: ls [-GRSaflrt1] [file ...]\n", STDERR);
	exit(EXIT_FAILURE);
}

static void		next_parse(t_list *file_list, t_list *dir_list, t_opts *flags,
																	char *cmd)
{
	t_list	*ptr;
	int		z;

	z = 0;
	(file_list) ? sort(file_list, flags) : NULL;
	(dir_list) ? sort(dir_list, flags) : NULL;
	(*flags & S_REVERSE) ? ft_lstinvert(&dir_list) : NULL;
	if (file_list)
	{
		print_list(&file_list, flags, TRUE);
		(*flags & MULTI_DIR) ? ft_putchar('\n') : NULL;
	}
	if (*flags & RECURSE)
	{
		ptr = dir_list;
		while (ptr)
		{
			recurse(((t_file*)ptr->content)->pathname, flags, 0, z++);
			ptr = ptr->next;
		}
	}
	else
		no_recurse(dir_list, flags, cmd);
	ft_lstdel(&file_list, &del);
	ft_lstdel(&dir_list, &del);
}

void			parse(int argc, char **argv, t_lst_duo *t, t_opts *flags)
{
	int			i;
	char		err;
	t_list		*input_lst;
	int			stop;

	input_lst = NULL;
	i = 0;
	stop = 0;
	while (++i < argc)
		if (!stop && !(ft_strncmp(argv[i], "--", 2)))
			stop = 1;
		else if (!stop && !input_lst && *argv[i] == '-' &&
					(ft_strncmp(argv[i], "--", 2)) && (ft_strlen(argv[i]) > 1))
		{
			if ((err = assign_flags(flags, argv[i] + 1)))
				error_msg(argv[0], err);
		}
		else
			(add_to_input(argv[i], &input_lst)) ? exit(-1) : NULL;
	*flags |= (input_lst && input_lst->next) ? MULTI_DIR : 0;
	if (!input_lst)
		(add_to_input(".", &input_lst)) ? exit(-1) : NULL;
	ft_list_sort(input_lst, &ft_strcmp);
	(assign_input(t, input_lst, argv[0])) ? exit(-1) : NULL;
	next_parse(t->lst_file, t->lst_dir, flags, argv[0]);
}
