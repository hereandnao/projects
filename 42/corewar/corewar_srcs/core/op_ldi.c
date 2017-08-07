/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <saubenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 15:48:34 by saubenne          #+#    #+#             */
/*   Updated: 2017/07/14 15:36:33 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

/*
** ldi : prend 2 index et 1 registre, additionne les 2 premiers,
** traite ca comme une adresse, y lit une valeur de la taille
** d’un registre et la met dans le 3eme
*/

void				op_ldi(t_env *e, t_process *process)
{
	int				tab[3];
	int				offset;
	int				i;
	int				reg_nb;

	if (e->flags & VERBOSE)
		ft_printf("{yellow}Round %.5d : p%.2i %s performing : LDI{eoc}\n",
		e->nb_cycle, process->nb, process->owner->file.prog_name);
	if ((offset = extractor(tab, e, process, 9)) == -1)
	{
		if (e->flags & VERBOSE)
			ft_printf("LDI fatal errror\n");
		return ;
	}
	i = (tab[0] + tab[1]) % IDX_MOD;
	i = (process->pc + i) & MEM_MASK;
	tab[2] = get_nb(e->map, i);
	reg_nb = e->map[((process->pc + offset - 1) & MEM_MASK)] - 1;
	process->reg[reg_nb] = tab[2];
	if (e->flags & VERBOSE)
		ft_printf("Ecriture de %d %#.8x dans le reg n°%d\n",
		tab[2], tab[2], reg_nb);
	process->pc = (process->pc + offset) & MEM_MASK;
}

/*
** lldi : Pareil que ldi, mais n’applique aucun modulo aux adresses.
** Modifie le carry.
*/

void				op_lldi(t_env *e, t_process *process)
{
	int				tab[3];
	int				offset;
	int				i;
	int				reg_nb;

	if (e->flags & VERBOSE)
		ft_printf("{yellow}Round %.5d : p%.2i - %s performing : LLDI{eoc}\n",
		e->nb_cycle, process->nb, process->owner->file.prog_name);
	if ((offset = extractor(tab, e, process, 13)) == -1)
	{
		if (e->flags & VERBOSE)
			ft_printf("LLDI fatal errror\n");
		return ;
	}
	i = (tab[0] + tab[1]);
	i = (process->pc + i) & MEM_MASK;
	tab[2] = get_nb(e->map, i);
	reg_nb = e->map[((process->pc + offset - 1) & MEM_MASK)] - 1;
	process->reg[reg_nb] = tab[2];
	if (e->flags & VERBOSE)
		ft_printf("Ecriture de %d dans le reg n°%d\n", tab[2], reg_nb);
	process->carry = (tab[2]) ? FALSE : TRUE;
	process->pc = (process->pc + offset) & MEM_MASK;
}
