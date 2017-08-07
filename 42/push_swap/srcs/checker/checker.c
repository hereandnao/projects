/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 17:03:18 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/10 14:10:31 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "checker.h"

static void		view_list(t_piles *p)
{
	t_node *tmp;

	tmp = p->a;
	ft_printf("{cyan}Pile A: {eoc}");
	while (tmp)
	{
		ft_printf("{cyan}%d {eoc}", tmp->nb);
		tmp = tmp->next;
		if (p->a == tmp)
			break ;
	}
	tmp = p->b;
	ft_printf("\n{yellow}Pile B: {eoc}");
	while (tmp)
	{
		ft_printf("{yellow}%d {eoc}", tmp->nb);
		tmp = tmp->next;
		if (p->b == tmp)
			break ;
	}
	ft_putchar('\n');
}

static int		make_op(char *s, t_piles *p)
{
	if (!(ft_strcmp(s, "sa")))
		sa(p);
	else if (!(ft_strcmp(s, "sb")))
		sb(p);
	else if (!(ft_strcmp(s, "ss")))
		ss(p);
	else if (!(ft_strcmp(s, "pa")))
		pa(p);
	else if (!(ft_strcmp(s, "pb")))
		pb(p);
	else if (!(ft_strcmp(s, "ra")))
		ra(p);
	else if (!(ft_strcmp(s, "rb")))
		rb(p);
	else if (!(ft_strcmp(s, "rr")))
		rr(p);
	else if (!(ft_strcmp(s, "rra")))
		rra(p);
	else if (!(ft_strcmp(s, "rrb")))
		rrb(p);
	else if (!(ft_strcmp(s, "rrr")))
		rrr(p);
	else
		return (0);
	return (1);
}

static int		reader(t_piles *p, int verbose)
{
	char	*line;
	int		i;

	if (verbose)
	{
		view_list(p);
		ft_printf("{magenta}Rules : s = swap, p = push, \
r = rotate, rr = reverse rotate\n{eoc}");
	}
	while ((i = get_next_line(0, &line)) == 1)
	{
		if (make_op(line, p) == 0)
			return (-1);
		if (verbose)
			view_list(p);
		free(line);
	}
	return (i);
}

static void		free_nodes(t_piles *p)
{
	while (p->a)
		del_node(&p->a);
	while (p->b)
		del_node(&p->b);
}

int				main(int argc, char **argv)
{
	t_piles		p;
	t_env		e;
	int			size;

	if (argc == 1)
		return (-1);
	ft_bzero(&e, sizeof(e));
	ft_bzero(&p, sizeof(t_piles));
	p.a = parse(argc, argv, &e, &size);
	if (!(p.a) || reader(&p, e.flags & INTERACTIF) == -1)
	{
		free_nodes(&p);
		return (ft_eprintf("Error\n"));
	}
	if (e.flags & INTERACTIF)
		view_list(&p);
	if (!(is_sorted(p.a)) || !p.a || p.b)
		ft_printf("KO\n");
	else
		ft_printf("OK\n");
	free_nodes(&p);
	return (0);
}
