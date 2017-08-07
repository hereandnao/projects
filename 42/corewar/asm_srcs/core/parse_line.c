/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 23:29:44 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/15 23:29:46 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"

static t_op		g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

static int		evalue(char *op_name, char *line, int n, char *err)
{
	if (!err && op_name)
		return (1);
	else if (!op_name)
		ft_eprintf(ERR_OP, line, n);
	else
		ft_eprintf(err, line, n);
	return (-1);
}

static int		prepare_line(char *line, char **n_line)
{
	int s;
	int e;
	int trim;

	s = 0;
	while (line[s] && (line[s] == '\t' || line[s] == ' '))
		s++;
	if (line[s] == '\0' || line[s] == ';' || line[s] == '#')
		return (0);
	e = 0;
	trim = 0;
	while (line[s + e] && line[s + e] != ';' && line[s + e] != '#')
	{
		trim = (line[s + e] == ' ' || line[s + e] == '\t') ? trim + 1 : 0;
		e++;
	}
	if (!(*n_line = (char *)malloc((e - trim + 1) * sizeof(char))))
		exit(EXIT_FAILURE);
	(*n_line)[e - trim] = '\0';
	ft_strncpy(*n_line, line + s, e - trim);
	return (1);
}

static void		norm_init(char **err, int *i)
{
	*err = NULL;
	*i = -1;
}

int				extract_instruction(char *line, t_map *map, int n)
{
	int			i;
	char		*n_line;
	char		*o_line;
	size_t		j;
	char		*err;

	o_line = line;
	if ((i = test_label_at_first(o_line, map)) < 0)
		return (0);
	if ((i = prepare_line(line += i, &n_line)) == 0)
		return (1);
	norm_init(&err, &i);
	while (g_op_tab[++i].name != NULL)
	{
		if (!ft_strncmp(n_line, g_op_tab[i].name,
(j = ft_strlen(g_op_tab[i].name))) && (n_line[j] == ' ' || n_line[j] == '\t'))
		{
			while (n_line[j] && (n_line[j] == ' ' || n_line[j] == '\t'))
				j++;
			err = write_instruction(n_line + j, &g_op_tab[i], map);
			break ;
		}
	}
	free(n_line);
	return (evalue(g_op_tab[i].name, o_line, n, err));
}

void			secure_lst(t_list **alst, t_list *new)
{
	if (new == NULL)
		exit(EXIT_FAILURE);
	ft_lstadd(alst, new);
}
