/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 17:17:59 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/10 14:08:26 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		free_nodes(t_piles *n, t_piles *p)
{
	while (n->a)
		del_node(&n->a);
	while (n->b)
		del_node(&n->b);
	if (p)
	{
		while (p->a)
			del_node(&p->a);
		while (p->b)
			del_node(&p->b);
	}
}

static void		test_solutions_verb(t_piles *p, int size,
								unsigned int (*f)(t_piles *, int, int, t_env *))
{
	t_piles			n;
	int				ratio;
	unsigned int	o_i;
	int				b;
	t_env			e;

	ft_printf("{green}-------- {yellow}Q_sort ^.--.^{green} --------{eoc}\n");
	ratio = 2;
	o_i = 0xFFFFFFFF;
	b = -1;
	while (ratio <= 20)
	{
		clone_pile(p, &n);
		ft_bzero(&e, sizeof(t_env));
		if (f(&n, size, ratio, &e) < o_i)
		{
			o_i = e.f_length;
			b = ratio;
		}
		ft_printf("ratio %2i -> q_sort: %-8u  A_len: %-5i  \
		B_len: %-5i sorted %s\n", ratio++, e.f_length, e.a_length, e.b_length, \
		(is_sorted(n.a) && !(n.b)) ? "OK" : "KO");
		free_nodes(&n, NULL);
	}
	ft_printf("Solution on pivot{red}%2i{eoc} : -> {yellow}%i{eoc}\n", b, o_i);
}

static void		resolve(t_piles *p, int size, t_env *e, t_res *res)
{
	if ((res->result_nao_q_sort < res->result_rra) && (res->result_nao_q_sort
															< res->result_ra))
	{
		ft_bzero(e, sizeof(t_env));
		e->to_write = TRUE;
		nao_q_sort(p, size, res->ratio, e);
	}
	else if (res->result_rra <= res->result_nao_q_sort &&
											(res->result_rra < res->result_ra))
		short_rra(p, size, TRUE);
	else
		short_ra(p, size, TRUE);
}

static void		get_solution(t_piles *p, int size)
{
	t_piles			n;
	t_res			res;
	t_env			e;
	int				ratio;

	ratio = 1;
	res.result_nao_q_sort = 0xFFFFFFFF;
	while (++ratio <= 20)
	{
		clone_pile(p, &n);
		ft_bzero(&e, sizeof(t_env));
		if (nao_q_sort(&n, size, ratio, &e) < res.result_nao_q_sort)
		{
			res.result_nao_q_sort = e.f_length;
			res.ratio = ratio;
		}
		free_nodes(&n, NULL);
	}
	n.a = clone_nodes(p->a);
	res.result_ra = short_ra(&n, size, FALSE);
	free_nodes(&n, NULL);
	n.a = clone_nodes(p->a);
	res.result_rra = short_rra(&n, size, FALSE);
	free_nodes(&n, NULL);
	resolve(p, size, &e, &res);
}

int				main(int argc, char **argv)
{
	t_piles			p;
	t_piles			n;
	t_args			args;
	int				size;

	ft_bzero(&args, sizeof(t_args));
	ft_bzero(&p, sizeof(t_piles));
	if (!(p.a = parse(argc, argv, &args, &size)))
		return (ft_eprintf("Error\n"));
	if (!(rationalize(p.a, size)))
		return (-1);
	n.a = clone_nodes(p.a);
	if (args.flags & VERBOSE)
	{
		view_list_verb(&p);
		ft_printf("{red}Solutions with q_sort:{eoc}\n");
		test_solutions_verb(&p, size, &nao_q_sort);
		ft_printf("Ra/sa -> {green}%u{eoc}\n", short_ra(&p, size, FALSE));
		ft_printf("Rra/sa -> {green}%u{eoc}\n", short_rra(&n, size, FALSE));
		ft_printf(((is_sorted(p.a) == 0) || !p.a || p.b) ? "KO\n" : "OK\n");
	}
	else
		get_solution(&p, size);
	free_nodes(&p, &n);
	return (0);
}
