/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 18:49:55 by saubenne          #+#    #+#             */
/*   Updated: 2017/07/06 16:56:15 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

int				get_nb(char *bf, int pc)
{
	int			res;

	res = (bf[pc & MEM_MASK]) & 0xff;
	res <<= 8;
	res |= (bf[(pc + 1) & MEM_MASK]) & 0xff;
	res <<= 8;
	res |= (bf[(pc + 2) & MEM_MASK]) & 0xff;
	res <<= 8;
	res |= (bf[(pc + 3) & MEM_MASK]) & 0xff;
	return (res);
}

static void		verb(t_env *e, t_process *p, t_list *tmp)
{
	if (tmp)
	{
		ft_printf("{blue_bg}Round %.5d : Live of %s's process for %s !"
		"{eoc}\n", e->nb_cycle, p->owner->file.prog_name,
		((t_warrior *)tmp->content)->file.prog_name);
	}
	else
	{
		ft_printf("{blue_bg}Round %.5d : Live of %s's process for nobody !"
		"{eoc}\n", e->nb_cycle, p->owner->file.prog_name);
	}
}

void			op_live(t_env *e, t_process *p)
{
	int			live_owner_nb;
	t_list		*tmp;

	if (e->flags & VERBOSE)
		ft_printf("{green}Round %.5d : p%.2d - %s performing :LIVE at %.4x"
		"{eoc}\n", e->nb_cycle, p->nb, p->owner->file.prog_name, p->pc);
	tmp = e->warriors;
	p->live += 1;
	live_owner_nb = get_nb(e->map, p->pc + 1);
	while (tmp)
	{
		if (((t_warrior *)tmp->content)->number == live_owner_nb)
			break ;
		tmp = tmp->next;
	}
	e->last_live = (tmp) ? ((t_warrior *)tmp->content) : e->last_live;
	if (e->flags & VERBOSE)
		verb(e, p, tmp);
	p->pc = (p->pc + 5) & MEM_MASK;
}

/*
** Jump to the given index if carry = 1
*/

void			op_zjmp(t_env *e, t_process *p)
{
	short		new_pc;

	if (e->flags & VERBOSE)
		ft_printf("{cyan_ul}Round %.5d : p%.2d - %s performing : ZJMP{eoc}\n",
					e->nb_cycle, p->nb, p->owner->file.prog_name);
	new_pc = e->map[(p->pc + 1) & MEM_MASK] & 0xff;
	new_pc = (new_pc << 8) | (e->map[(p->pc + 2) & MEM_MASK] & 0xff);
	new_pc %= IDX_MOD;
	if (p->carry == TRUE)
		p->pc = (p->pc + new_pc) & MEM_MASK;
	else
	{
		if (e->flags & VERBOSE)
			ft_printf("JUMP FAILED ! *BLOMB*\n");
		p->pc = (p->pc + 3) & MEM_MASK;
	}
}

/*
** Write a char
*/

void			op_aff(t_env *e, t_process *p)
{
	int			tab[3];
	int			offset;

	if (e->flags & VERBOSE)
		ft_printf("{green}Round %.5d : p%.2d - %s performing : AFF{eoc}\n",
				e->nb_cycle, p->nb, p->owner->file.prog_name);
	if ((offset = extractor(tab, e, p, 15)) == -1)
	{
		if (e->flags & VERBOSE)
			ft_printf("AFF fatal error\n");
		return ;
	}
	ft_putchar(tab[0]);
	ft_putchar('\n');
	p->pc = (p->pc + offset) & MEM_MASK;
}
