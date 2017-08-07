/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_logical.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 18:50:04 by saubenne          #+#    #+#             */
/*   Updated: 2017/07/01 18:50:07 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

/*
** Bytecode values :
** registrer = 01
**  indirect = 11
**	direct = 10
*/

/*
** Separate each part of the bytecode
** if arg1 & arg2 == 0, carry = TRUE
*/

void				op_and(t_env *e, t_process *process)
{
	int				tab[3];
	int				offset;
	int				reg;

	if (e->flags & VERBOSE)
		ft_printf("{light_blue}Round %.5d : p%.2d - %s performing : AND{eoc}\n",
		e->nb_cycle, process->nb, process->owner->file.prog_name);
	if ((offset = extractor(tab, e, process, 5)) == -1)
		return ;
	reg = e->map[process->pc + offset - 1] & MEM_MASK;
	reg--;
	process->reg[reg] = tab[0] & tab[1];
	process->carry = (process->reg[reg] == 0) ? TRUE : FALSE;
	process->pc = (process->pc + offset) & MEM_MASK;
}

void				op_or(t_env *e, t_process *process)
{
	int				tab[3];
	int				offset;
	int				reg;

	if (e->flags & VERBOSE)
		ft_printf("{light_blue}Round %.5d : p%.2d - %s performing : OR{eoc}\n",
		e->nb_cycle, process->nb, process->owner->file.prog_name);
	if ((offset = extractor(tab, e, process, 6)) == -1)
		return ;
	reg = e->map[process->pc + offset - 1] & MEM_MASK;
	reg--;
	process->reg[reg] = tab[0] | tab[1];
	process->carry = (process->reg[reg] == 0) ? TRUE : FALSE;
	process->pc = (process->pc + offset) & MEM_MASK;
}

void				op_xor(t_env *e, t_process *process)
{
	int				tab[3];
	int				offset;
	int				reg;

	if (e->flags & VERBOSE)
		ft_printf("{light_blue}Round %.5d : p%.2d - %s performing : XOR{eoc}\n",
		e->nb_cycle, process->nb, process->owner->file.prog_name);
	if ((offset = extractor(tab, e, process, 7)) == -1)
		return ;
	reg = e->map[process->pc + offset - 1] & MEM_MASK;
	reg--;
	process->reg[reg] = tab[0] ^ tab[1];
	process->carry = (process->reg[reg] == 0) ? TRUE : FALSE;
	process->pc = (process->pc + offset) & MEM_MASK;
}
