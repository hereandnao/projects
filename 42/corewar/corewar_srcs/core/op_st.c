/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
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
** st : Prend un registre et un registre ou un indirect, et stocke la
** valeur du registre vers le second paramètre. Son opcode est 0x03.
*/

static int			get_err_offset(char bytecode, int nb, int v_size)
{
	int				offset;
	int				i;
	int				j;

	offset = 0;
	i = 6;
	while (nb--)
	{
		j = (bytecode >> i) & 0b11;
		if (j == REG_CODE)
			offset += 1;
		else if (j == IND_CODE)
			offset += 2;
		else if (j == DIR_CODE)
			offset += (v_size) ? 2 : 4;
		i -= 2;
	}
	return (offset);
}

static void			st_reg_to_reg(t_env *e, t_process *process)
{
	int				offset;
	int				val_p1;
	int				val_p2;
	int				error;

	offset = 2;
	error = FALSE;
	val_p1 = get_reg_value(e->map, process, &offset, &error);
	val_p2 = e->map[(process->pc + 3) & MEM_MASK] - 1;
	error |= (val_p2 >= 0 && val_p2 <= 15) ? FALSE : TRUE;
	if (error)
	{
		process->pc = (process->pc + 4) & MEM_MASK;
		if (e->flags & VERBOSE)
			ft_printf("ST fatal errror -> Register too big !");
		return ;
	}
	process->reg[val_p2] = val_p1;
	if (e->flags & VERBOSE)
		ft_printf("ST: reg2reg -> Ecriture valeur %#x dans reg dest : %i\n",
															val_p1, val_p2);
	process->pc = (process->pc + 4) & MEM_MASK;
}

static void			st_ind_to_reg(t_env *e, t_process *process)
{
	int				offset;
	int				val_p1;
	int				val_p2;
	int				error;

	offset = 2;
	error = FALSE;
	val_p1 = get_reg_value(e->map, process, &offset, &error);
	if (error)
	{
		process->pc = (process->pc + 5) & MEM_MASK;
		return ;
	}
	val_p2 = extract_dir(process, e->map, &offset, TRUE) % IDX_MOD;
	write_field(e->map,
		(val_p2 + process->pc) & MEM_MASK, val_p1);
	if (e->flags & VERBOSE)
		ft_printf("ST: ind2reg -> Ecriture valeur %#x a relativ dest :\
		%i -> absolute %i\n",
		val_p1, val_p2, (val_p2 + process->pc) & MEM_MASK);
	process->pc = (process->pc + 5) & MEM_MASK;
}

void				op_st(t_env *e, t_process *process)
{
	char			bytecode;

	if (e->flags & VERBOSE)
		ft_printf("{green}Round %.5d : p%.2d - %s performing : ST{eoc}\n",
		e->nb_cycle, process->nb, process->owner->file.prog_name);
	bytecode = e->map[(process->pc + 1) & MEM_MASK];
	if ((bytecode & 0b11110000) != 0b01110000 &&
	(bytecode & 0b11110000) != 0b01010000)
	{
		if (e->flags & VERBOSE)
			ft_printf("ST fatal error -> offset += %i\n",
											get_err_offset(bytecode, 2, 0));
		process->pc += get_err_offset(bytecode, 2, 0) + 2;
		process->pc &= MEM_MASK;
	}
	else if ((bytecode & 0b11110000) == 0b01010000)
		st_reg_to_reg(e, process);
	else
		st_ind_to_reg(e, process);
}
