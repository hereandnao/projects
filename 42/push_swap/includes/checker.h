/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:31:17 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/02 14:31:25 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include <limits.h>
# include "libft.h"

# define STDERR 2
# define STDIO 1

typedef enum		e_opts
{
	READ_FILE = 0x02,
	INTERACTIF = 0x01
}					t_opts;

typedef struct		s_env
{
	t_opts			flags;
	int				error;
}					t_env;

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

typedef struct		s_op
{
	char			*str;
	void			(*f)(t_piles *p);
}					t_op;

t_node				*parse(int argc, char **argv, t_env *e, int *size);
void				push_front(t_node **lstnode, int nb);
void				push_back(t_node **begin, int nb);
void				del_node(t_node **node);
void				del_node(t_node **node);
int					is_sorted(t_node *a);
int					read_file(char *name, t_node **n, int *size);
int					ft_special_secure_atoi(const char *nptr, int *error);

void				sa(t_piles *p);
void				sb(t_piles *p);
void				ss(t_piles *p);
void				pa(t_piles *p);
void				pb(t_piles *p);
void				ra(t_piles *p);
void				rb(t_piles *p);
void				rr(t_piles *p);
void				rra(t_piles *p);
void				rrb(t_piles *p);
void				rrr(t_piles *p);

#endif
