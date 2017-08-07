/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <saubenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 18:48:49 by saubenne          #+#    #+#             */
/*   Updated: 2017/07/14 14:04:45 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

void				op_fork(t_env *e, t_process *process)
{
	int				offset;
	int				v;

	offset = 1;
	if (e->flags & VERBOSE)
		ft_printf("{green}Round %.5d, p%.2d - %s FORK !{eoc}\n",
		e->nb_cycle, process->nb, process->owner->file.prog_name);
	v = extract_dir(process, e->map, &offset, TRUE);
	v %= IDX_MOD;
	clone_process(&e->process, process, e);
	e->process->pc = (process->pc + v) & MEM_MASK;
	process->pc = (process->pc + offset) & MEM_MASK;
}

void				op_lfork(t_env *e, t_process *process)
{
	int				offset;
	int				v;

	offset = 1;
	if (e->flags & VERBOSE)
		ft_printf("{green}Round %.5d, p%.2d - %s LFORK !{eoc}\n",
		e->nb_cycle, process->nb, process->owner->file.prog_name);
	v = extract_dir(process, e->map, &offset, TRUE);
	clone_process(&e->process, process, e);
	e->process->pc = (process->pc + v) & MEM_MASK;
	process->pc = (process->pc + offset) & MEM_MASK;
}
