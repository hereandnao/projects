/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:31:17 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/10 15:32:01 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include "libft.h"
# include <stdlib.h>

# define STDERR 2
# define STDIO 1

typedef enum		e_opts
{
	READ_FILE = 0x02,
	VERBOSE = 0x01
}					t_opts;

typedef struct		s_args
{
	t_opts			flags;
	int				error;
}					t_args;

typedef struct		s_node
{
	int				nb;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct		s_piles
{
	t_node			*a;
	t_node			*b;
}					t_piles;

typedef struct		s_env
{
	int				a_length;
	int				b_length;
	int				f_length;
	int				trigger;
	int				to_write;
}					t_env;

typedef struct		s_res
{
	int				ratio;
	unsigned int	result_ra;
	unsigned int	result_rra;
	unsigned int	result_nao_q_sort;
}					t_res;

int					push_front(t_node **lstnode, int nb);
int					push_back(t_node **begin, int nb);
void				del_node(t_node **node);

t_node				*parse(int argc, char **argv, t_args *e, int *size);
int					read_file(char *name, t_node **n, int *size);
int					ft_special_secure_atoi(const char *nptr, int *error);

int					is_sorted(t_node *a);
int					rationalize(t_node *n, int size);
void				view_list(t_piles *p);
void				view_list_verb(t_piles *p);
t_node				*clone_nodes(t_node *original);
void				clone_pile(t_piles *p, t_piles *n);

unsigned int		short_rra(t_piles *p, int size, int to_write);
unsigned int		short_ra(t_piles *p, int size, int to_write);

unsigned int		nao_q_sort(t_piles *p, int size, int ratio, t_env *e);
int					l_choose_pivot(int pivot, int size, int ratio);
int					l_below_than_piv(t_node *a, int pivot);
void				l_move_to_higher(t_piles *p, t_env *e, int max,
																int do_write);

int					sa(t_piles *p, int do_write);
int					sb(t_piles *p, int do_write);
int					ss(t_piles *p, int do_write);
int					pa(t_piles *p, int do_write);
int					pb(t_piles *p, int do_write);
int					ra(t_piles *p, int do_write);
int					rb(t_piles *p, int do_write);
int					rr(t_piles *p, int do_write);
int					rra(t_piles *p, int do_write);
int					rrb(t_piles *p, int do_write);
int					rrr(t_piles *p, int do_write);

#endif
