/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:36:28 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/02 14:36:31 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

static int		assign_flags(char *s, t_opts *flags)
{
	while (*s)
	{
		if (*s == 'v')
			*flags |= VERBOSE;
		else if (*s == 'f')
			*flags |= READ_FILE;
		else
			return ((int)*s);
		s++;
	}
	return (0);
}

static void		error_msg(char *cmd, char letter)
{
	ft_eprintf("%s : illegal option -- %c\nusage: %s [-v] [List ...] || [-f]\
[Input file]\n", cmd, letter, cmd, STDERR);
	exit(EXIT_FAILURE);
}

static int		check_same(t_node *node)
{
	t_node *tmp_a;
	t_node *tmp_b;

	if (!(tmp_a = node))
		return (0);
	if (tmp_a == tmp_a->next)
		return (1);
	while (TRUE)
	{
		if ((tmp_b = tmp_a->next) == node)
			return (1);
		while (TRUE)
		{
			if (tmp_a->nb == tmp_b->nb)
				return (0);
			if ((tmp_b = tmp_b->next) == node)
				break ;
		}
		tmp_a = tmp_a->next;
		if (tmp_a == node)
			break ;
	}
	return (1);
}

static void		init_values(int *i, t_node **a, int *size)
{
	*i = 0;
	*a = NULL;
	*size = 0;
}

t_node			*parse(int argc, char **argv, t_args *e, int *size)
{
	t_node		*a;
	int			i;

	init_values(&i, &a, size);
	while (++i < argc)
		if (!a && *argv[i] == '-' && (ft_strlen(argv[i]) > 1)
								&& !(argv[i][1] >= '0' && argv[i][1] <= '9'))
		{
			if ((e->error = assign_flags(argv[i] + 1, &e->flags)))
				error_msg(argv[0], (char)e->error);
		}
		else if (e->flags & READ_FILE)
		{
			if (!(read_file(argv[i], &a, size)))
				return (NULL);
			break ;
		}
		else
		{
			*size += 1;
			push_back(&a, ft_secure_atoi(argv[i], &e->error));
			if (e->error)
				return (NULL);
		}
	return ((check_same(a) ? a : NULL));
}
