/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <saubenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 18:50:25 by saubenne          #+#    #+#             */
/*   Updated: 2017/07/18 17:53:01 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

/*
** ld: Prend un paramètre quelconque et un registre. Charge la valeur du premier
** paramètre dans le registre. Change le carry.
*/

void				op_ld(t_env *e, t_process *process)
{
	int				tab[3];
	int				offset;

	if (e->flags & VERBOSE)
		ft_printf("{yellow}Round %.5d : p%.2i - %s performing : LD{eoc}\n",
		e->nb_cycle, process->nb, process->owner->file.prog_name);
	if ((offset = extractor(tab, e, process, 1)) == -1)
	{
		if (e->flags & VERBOSE)
			ft_printf("LD fatal errror\n");
		return ;
	}
	tab[1] = e->map[((process->pc + offset - 1) & MEM_MASK)] - 1;
	if (!(tab[1] >= 0 && tab[1] <= 15))
	{
		if (e->flags & VERBOSE)
			ft_printf("LD fatal errror, reg too big !\n");
		process->pc = (process->pc + offset) & MEM_MASK;
		return ;
	}
	process->carry = (tab[0]) ? FALSE : TRUE;
	process->reg[tab[1]] = tab[0];
	if (e->flags & VERBOSE)
		ft_printf("LD Success : res = %d reg = %d\n", tab[0], tab[1]);
	process->pc = (process->pc + offset) & MEM_MASK;
}

/*
** lld : Signifie long-load, donc son opcode est évidemment 13. Même chose
** que ld, mais sans % IDX_MOD. Modifie le carry.
*/

void				op_lld(t_env *e, t_process *process)
{
	int				tab[3];
	int				offset;

	if (e->flags & VERBOSE)
		ft_printf("{yellow}Round %.5d : p%.2i - %s performing : LD{eoc}\n",
		e->nb_cycle, process->nb, process->owner->file.prog_name);
	if ((offset = extractor(tab, e, process, 12)) == -1)
	{
		if (e->flags & VERBOSE)
			ft_printf("LD fatal errror\n");
		return ;
	}
	tab[1] = e->map[((process->pc + offset - 1) & MEM_MASK)] - 1;
	if (!(tab[1] >= 0 && tab[1] <= 15))
	{
		if (e->flags & VERBOSE)
			ft_printf("LD fatal errror, reg too big !\n");
		process->pc = (process->pc + offset) & MEM_MASK;
		return ;
	}
	process->carry = (tab[0]) ? FALSE : TRUE;
	process->reg[tab[1]] = tab[0];
	if (e->flags & VERBOSE)
		ft_printf("LD Success : res = %d reg = %d\n", tab[0], tab[1]);
	process->pc = (process->pc + offset) & MEM_MASK;
}
