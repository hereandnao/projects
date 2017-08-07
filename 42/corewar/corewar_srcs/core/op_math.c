/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <saubenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 18:50:36 by saubenne          #+#    #+#             */
/*   Updated: 2017/07/14 15:31:28 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

/*
** Prend trois registres, additionne les 2 premiers, et met le résultat
** dans le troisième, juste avant de modifier le carry
** Could use REG_NBR instead of 16 but SPACE
** As we start from reg[0], got to search in reg[r - 1]
*/

void				op_add(t_env *e, t_process *process)
{
	int				tab[3];
	int				offset;
	int				i;

	if (e->flags & VERBOSE)
		ft_printf("{blue}Round %.5d : p%.2d - %s performing : ADD{eoc}\n",
			e->nb_cycle, process->nb, process->owner->file.prog_name);
	if ((offset = extractor(tab, e, process, 3)) == -1)
	{
		if (e->flags & VERBOSE)
			ft_printf("ADD fatal errror\n");
		return ;
	}
	i = e->map[(process->pc + offset - 1) & MEM_MASK] - 1;
	process->reg[i] = tab[0] + tab[1];
	process->carry = (process->reg[i]) ? FALSE : TRUE;
	process->pc = (process->pc + offset) & MEM_MASK;
	if (e->flags & VERBOSE)
		ft_printf("ADD Success : %d + %i in register %i\n", tab[0], tab[1], i);
}

/*
**	Prend trois registres, soustrait les 2 premiers, et met le résultat
** dans le troisième, juste avant de modifier le carry
*/

void				op_sub(t_env *e, t_process *process)
{
	int				tab[3];
	int				offset;
	int				i;

	if (e->flags & VERBOSE)
		ft_printf("{blue}Round %.5d : p%.2d - %s performing : SUB{eoc}\n",
			e->nb_cycle, process->nb, process->owner->file.prog_name);
	if ((offset = extractor(tab, e, process, 4)) == -1)
	{
		if (e->flags & VERBOSE)
			ft_printf("SUB fatal errror\n");
		return ;
	}
	i = e->map[(process->pc + offset - 1) & MEM_MASK] - 1;
	process->reg[i] = tab[0] - tab[1];
	process->carry = (process->reg[i]) ? FALSE : TRUE;
	process->pc = (process->pc + offset) & MEM_MASK;
	if (e->flags & VERBOSE)
		ft_printf("SUB Success : %d + %i in register %i\n", tab[0], tab[1], i);
}
