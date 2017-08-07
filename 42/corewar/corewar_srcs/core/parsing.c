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

#include <stdlib.h>
#include "libft.h"
#include "vm.h"

int					set_player(int *i, int rab, t_list **alst, char **argv)
{
	int				error;
	int				n;
	t_champ_num		*s;

	error = FALSE;
	n = 0;
	if (!ft_strcmp("-n", argv[*i]) || !ft_strcmp("--number", argv[*i]))
	{
		if (rab < 3)
			return (1);
		(*i)++;
		n = ft_secure_atoi(argv[*i], &error);
		if (error || n < 1)
			return (1);
		(*i)++;
	}
	if (!(s = (t_champ_num *)malloc(sizeof(t_champ_num))))
		exit(EXIT_FAILURE);
	s->name = argv[*i];
	s->nb = n;
	if (!(ft_lst_push_front(alst, s, sizeof(void *))))
		exit(EXIT_FAILURE);
	(*i)++;
	return (0);
}

int					set_dump(t_env *e, int *i, int rab, char **argv)
{
	int error;

	if (e->flags & DUMP || rab < 2)
	{
		ft_eprintf("Invalid dump command, may be already dumped !\n");
		return (1);
	}
	(*i)++;
	error = FALSE;
	e->dump_value = ft_secure_atoi(argv[*i], &error);
	if (error || e->dump_value < 0)
	{
		ft_eprintf("Invalid dump value: %s !\n", argv[*i]);
		return (1);
	}
	e->flags |= DUMP;
	(*i)++;
	return (0);
}

int					set_graphic(t_env *e, int *i)
{
	if (e->flags & GRAPHIC)
	{
		ft_eprintf("Already graphiced !\n");
		return (1);
	}
	e->flags |= GRAPHIC;
	(*i)++;
	return (0);
}

int					set_verbose(t_env *e, int *i)
{
	if (e->flags & VERBOSE)
	{
		ft_eprintf("Already verbosed !\n");
		return (1);
	}
	e->flags |= VERBOSE;
	(*i)++;
	return (0);
}

t_list				*parsing(int argc, char **argv, t_env *e)
{
	int				i;
	t_list			*input_lst;
	int				err;

	input_lst = NULL;
	i = 1;
	err = FALSE;
	while (i < argc && (err == FALSE))
	{
		if (!ft_strcmp("-v", argv[i]) || !ft_strcmp("--verbose", argv[i]))
			err |= set_verbose(e, &i);
		else if (!ft_strcmp("-g", argv[i]) || !ft_strcmp("--graphic", argv[i]))
			err |= set_graphic(e, &i);
		else if (!ft_strcmp("-d", argv[i]) || !ft_strcmp("--dump", argv[i]))
			err |= set_dump(e, &i, argc - i, argv);
		else if ((err |= set_player(&i, argc - i, &input_lst, argv)))
			ft_eprintf("Invalid player !\n");
	}
	if (err)
		free_t_list(input_lst);
	return ((err) ? NULL : input_lst);
}
