/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 16:35:02 by saubenne          #+#    #+#             */
/*   Updated: 2017/07/08 14:57:19 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "vm.h"

static void			nao_bubble(t_list *lst, t_list *origin)
{
	void			*tmp;
	int				trigger;

	trigger = TRUE;
	while (trigger)
	{
		trigger = FALSE;
		lst = origin;
		while (lst->next)
		{
			if (((t_champ_num *)lst->content)->nb >
			((t_champ_num *)lst->next->content)->nb)
			{
				trigger = TRUE;
				tmp = lst->content;
				lst->content = lst->next->content;
				lst->next->content = tmp;
			}
			lst = lst->next;
		}
	}
}

t_list				*free_t_list(t_list *lst)
{
	t_list *tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp);
	}
	return (NULL);
}

static t_list		*read_warriors(t_list *current, char *c)
{
	t_list			*lst_warrior;
	unsigned int	file_size;
	t_warrior		*tmp;
	char			*ch_name;
	char			*bout;

	lst_warrior = NULL;
	while (current)
	{
		ch_name = ((t_champ_num *)current->content)->name;
		bout = ft_strrchr(ch_name, '.');
		if (bout == NULL || ft_strcmp(bout, ".cor"))
		{
			ft_printf("Name \"%s\" incorrect ! Must be a .cor file\n", ch_name);
			return (free_t_list(lst_warrior));
		}
		if ((tmp = (t_warrior *)read_file(ch_name, &file_size, c)) == NULL)
			return (free_t_list(lst_warrior));
		if (ft_lst_push_front(&lst_warrior, tmp, sizeof(t_warrior)) == NULL)
			exit(EXIT_FAILURE);
		if ((get_real_size(tmp->file.prog_size) + 2192) != file_size)
			return (err_bad_size(lst_warrior));
		current = current->next;
	}
	return (lst_warrior);
}

static int			count_champions(t_list *lst)
{
	int				i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int					main(int argc, char **argv)
{
	t_env			env;
	t_list			*list;
	char			c;

	ft_bzero(&env, sizeof(t_env));
	if (!(list = parsing(argc, argv, &env)))
	{
		ft_printf("parsing error\n");
		return (-1);
	}
	ft_lst_invert_it(&list);
	if ((env.nb_players = count_champions(list)) < MIN_PLAYERS ||
		env.nb_players > MAX_PLAYERS)
	{
		ft_eprintf("bad count of champions ! Have %i !\n", env.nb_players);
		return (-1);
	}
	nao_bubble(list, list);
	if (!(env.warriors = read_warriors(list, &c)))
		return (-1);
	free_t_list(list);
	manage_champions(&env);
	time_machine(&env);
	free_all_process(&env.process);
	return ((int)free_t_list(env.warriors));
}
