/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <saubenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 18:50:52 by saubenne          #+#    #+#             */
/*   Updated: 2017/07/15 12:19:24 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

static void			write_field(char map[MEM_SIZE], int pc,
																int value)
{
	map[pc++ & MEM_MASK] = (value >> 24) & 0xff;
	map[pc++ & MEM_MASK] = (value >> 16) & 0xff;
	map[pc++ & MEM_MASK] = (value >> 8) & 0xff;
	map[pc & MEM_MASK] = value & 0xff;
}

/*
** sti: Opcode 11. Prend un registre, et deux index (potentiellement des
** registres). Additionne les deux derniers, utilise cette somme comme une
** adresse ou sera copiée la valeur du premier paramètre
*/

void				op_sti(t_env *e, t_process *process)
{
	int				tab[3];
	int				offset;
	int				i;

	if (e->flags & VERBOSE)
		ft_printf("{green}Round %.5d : p%.2d - %s performing :\
		STI at %.4x{eoc}\n",
		e->nb_cycle, process->nb, process->owner->file.prog_name, process->pc);
	if ((offset = extractor(tab, e, process, 10)) == -1)
	{
		if (e->flags & VERBOSE)
			ft_printf("STI fatal errror\n");
		return ;
	}
	i = (tab[1] + tab[2]) % IDX_MOD;
	i = (process->pc + i) & MEM_MASK;
	write_field(e->map, i, tab[0]);
	if (e->flags & VERBOSE)
		ft_printf("STI: Ecriture du %.8x offset = %i, %i\n", tab[0], tab[1],
																		tab[2]);
	process->pc = (process->pc + offset) & MEM_MASK;
}
