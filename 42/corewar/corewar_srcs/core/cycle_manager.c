/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <saubenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 18:52:00 by saubenne          #+#    #+#             */
/*   Updated: 2017/07/14 13:49:48 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

const t_op			g_op_tab[N_OP] =
{
	{"live", 0x01, 9, 1, {T_DIR}, 0, UNUSED, &op_live},
	{"ld", 0x02, 4, 2, {T_DIR | T_IND, T_REG}, 0, TRUE, &op_ld},
	{"st", 0x03, 4, 2, {T_REG, T_IND | T_REG}, 0, TRUE, &op_st},
	{"add", 0x04, 9, 3, {T_REG, T_REG, T_REG}, 0, UNUSED, &op_add},
	{"sub", 0x05, 9, 3, {T_REG, T_REG, T_REG}, 0, UNUSED, &op_sub},
	{"and", 0x06, 5, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		0, TRUE, &op_and},
	{"or", 0x07, 5, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		0, TRUE, &op_or},
	{"xor", 0x08, 5, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		0, TRUE, &op_xor},
	{"zjmp", 0x09, 19, 1, {T_DIR}, 1, UNUSED, &op_zjmp},
	{"ldi", 0x0A, 24, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		1, TRUE, &op_ldi},
	{"sti", 0x0B, 24, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		1, TRUE, &op_sti},
	{"fork", 0x0C, 799, 1, {T_DIR}, 1, TRUE, &op_fork},
	{"lld", 0x0D, 9, 2, {T_DIR | T_IND, T_REG}, 0, FALSE, &op_lld},
	{"lldi", 0x0E, 49, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		1, FALSE, &op_lldi},
	{"lfork", 0x0F, 999, 1, {T_DIR}, 1, FALSE, &op_lfork},
	{"aff", 0x10, 1, 1, {T_REG}, 0, UNUSED, &op_aff}
};

/*
** ft_printf("the winner is %s\n", e->last_live->file.prog_name);
*/

static void			get_winner(t_env *e)
{
	if (e->last_live != NULL)
		ft_printf("And the winner is %s !\n", e->last_live->file.prog_name);
	else
		ft_printf("There is no Winner :(\n");
}

static void			assign_task(char value, t_process *process, t_env *e)
{
	if (value >= 1 && value <= 16)
	{
		process->fn = g_op_tab[value - 1].fn;
		process->countdown = g_op_tab[value - 1].duration;
		return ;
	}
	if (e->flags & VERBOSE)
		ft_printf("{green}Round %.5d : Le process |p.%4d| ne fait rien !\
			pos = %.4x{eoc}\n", e->nb_cycle, process->nb, process->pc);
	process->pc = (process->pc + 1) & MEM_MASK;
	return ;
}

static int			time_round(t_env *e, int cycle_to_die)
{
	t_process		*lst;
	static int		i = 0;

	if (e->flags & VERBOSE)
		ft_printf("{magenta}Round n#%i, Cycle_to_die = %i{eoc}\n", i++,
															cycle_to_die);
	while (cycle_to_die--)
	{
		if ((e->flags & DUMP) && (e->nb_cycle == e->dump_value))
			return (72);
		e->nb_cycle += 1;
		lst = e->process;
		while (lst)
		{
			if (!lst->fn)
				assign_task(e->map[lst->pc], lst, e);
			else if (!(--(lst->countdown)))
			{
				lst->fn(e, lst);
				lst->fn = NULL;
			}
			lst = lst->next;
		}
	}
	return (0);
}

void				time_machine(t_env *e)
{
	int				cycle_to_die;
	int				checks;
	int				live;

	checks = 0;
	cycle_to_die = CYCLE_TO_DIE;
	while (cycle_to_die > 0 && e->process)
	{
		if (time_round(e, cycle_to_die) == 72)
			break ;
		if (e->flags & VERBOSE)
			ft_printf("{red}Round n#%i : Time to die !{eoc}\n", e->nb_cycle);
		live = destroy_process(&e->process);
		if (live >= NBR_LIVE || checks == MAX_CHECKS)
		{
			checks = 1;
			cycle_to_die -= CYCLE_DELTA;
		}
		else
			checks++;
	}
	if ((e->flags & DUMP) && (e->nb_cycle == e->dump_value) && e->process)
		display_map(e->map);
	else
		get_winner(e);
}
