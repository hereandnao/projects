/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_champions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 16:35:02 by saubenne          #+#    #+#             */
/*   Updated: 2017/06/26 16:35:03 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

static void			fill_champions(t_env *env)
{
	int				j;
	char			*data;
	t_list			*lst;
	int				pc;

	lst = env->warriors;
	j = 0;
	while (j < env->nb_players)
	{
		pc = j * (MEM_SIZE / env->nb_players);
		data = ((t_warrior *)lst->content)->file.data;
		ft_memcpy(env->map + pc, data,
		get_real_size(((t_warrior *)lst->content)->file.prog_size));
		create_process(((t_warrior *)lst->content), pc, &env->process, env);
		lst = lst->next;
		j++;
	}
}

void				manage_champions(t_env *env)
{
	int				i;
	t_warrior		*tmp;
	t_list			*lst;

	ft_lst_invert_it(&env->warriors);
	ft_printf("Introducing contestants...\n");
	i = -1;
	lst = env->warriors;
	while (lst)
	{
		tmp = lst->content;
		tmp->number = i;
		ft_printf("* Player %i, weighing %u bytes, \"%s\" (\"%s\") !\n",
		-tmp->number, get_real_size(tmp->file.prog_size), tmp->file.prog_name,
															tmp->file.comment);
		i--;
		lst = lst->next;
	}
	fill_champions(env);
}
