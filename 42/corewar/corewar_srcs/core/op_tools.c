/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 02:32:48 by saubenne          #+#    #+#             */
/*   Updated: 2017/07/16 02:33:13 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

/*
** Si la valeur à extraire est soumise à v_size
** (2 octes pour un direct), il est necessaire de caster le int (4 octet) en
** short int (2 octes)
*/

static int			verif(unsigned char nb, const t_op *g, int *offset, int i)
{
	int				res;
	int				error;

	error = FALSE;
	while (++i < g->param_nb)
		if ((res = (nb >> (6 - (2 * i))) & 0b11) == REG_CODE)
		{
			*offset += 1;
			if (!(g->naocode[i] & T_REG))
				error = TRUE;
		}
		else if (res == DIR_CODE)
		{
			*offset += (g->v_size) ? 2 : 4;
			error = (!(g->naocode[i] & T_DIR)) ? TRUE : error;
		}
		else if (res == IND_CODE)
		{
			*offset += 2;
			if (!(g->naocode[i] & T_IND))
				error = TRUE;
		}
		else
			error = TRUE;
	return ((error) ? -1 : 0);
}

/*
** Cett fonction est plus comprehensible si vous imaginez que nb est egal a 72.
*/

int					jenaimarre(int tab[3], t_highway *h, int n)
{
	int				offset;
	int				error;
	int				res;
	int				i;

	i = -1;
	error = FALSE;
	offset = 2;
	while (++i < g_op_tab[n].param_nb)
		if ((res = (h->nb >> (6 - (2 * i))) & 0b11) == 0b01)
		{
			tab[i] = get_reg_value(h->e->map, h->p, &offset, &error);
			if (error)
			{
				h->p->pc = (h->p->pc + h->tmp) & MEM_MASK;
				return (-1);
			}
		}
		else if (res == 0b10)
			tab[i] = extract_dir(h->p, h->e->map, &offset, g_op_tab[n].v_size);
		else if (res == 0b11)
			tab[i] = extract_ind(h->p, h->e->map, &offset, g_op_tab[n].idx);
	return (offset);
}

int					extractor(int tab[3], t_env *e, t_process *process, int n)
{
	t_highway		highway;
	unsigned char	nb;
	int				i;
	int				tmp;

	tmp = 2;
	i = -1;
	nb = e->map[(process->pc + 1) & MEM_MASK];
	if ((verif(nb, &g_op_tab[n], &tmp, i)) == -1)
	{
		if (e->flags & VERBOSE)
			ft_printf("Invalid Bytecode\n");
		process->pc = (process->pc + tmp) & MEM_MASK;
		return (-1);
	}
	highway.nb = nb;
	highway.tmp = tmp;
	highway.e = e;
	highway.p = process;
	return (jenaimarre(tab, &highway, n));
}

/*
**	Direct = read the value of the tile
*/

int					extract_dir(t_process *process, char field[MEM_SIZE],
													int *offset, int v_size)
{
	int				output;
	int				i;

	i = (process->pc + *offset) & MEM_MASK;
	*offset += (v_size) ? 2 : 4;
	output = field[i] & 0xff;
	output = (output << 8) + (field[++i & MEM_MASK] & 0xff);
	if (v_size)
	{
		output = (short int)output;
		return (output);
	}
	output = (output << 8) + (field[++i & MEM_MASK] & 0xff);
	output = (output << 8) + (field[++i & MEM_MASK] & 0xff);
	return (output);
}

/*
** Indirect : add the read nb to current pc and get the value of the sum tile
*/

int					extract_ind(t_process *process, char field[MEM_SIZE],
													int *offset, int idx_mod)
{
	int				output;
	int				i;
	int				res;

	i = (process->pc + *offset) & MEM_MASK;
	*offset += 2;
	output = field[i] & 0xff;
	output = (output << 8) + (field[++i & MEM_MASK] & 0xff);
	output = (short)output;
	if (idx_mod)
		output = output % IDX_MOD;
	i = (process->pc + output) & MEM_MASK;
	res = field[i] & 0xff;
	res = (res << 8) + (field[++i & MEM_MASK] & 0xff);
	res = (res << 8) + (field[++i & MEM_MASK] & 0xff);
	res = (res << 8) + (field[++i & MEM_MASK] & 0xff);
	return (res);
}
