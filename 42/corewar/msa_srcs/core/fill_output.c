/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 21:13:00 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/27 21:13:01 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "msa.h"
#include "wof/wof.h"

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

static int		write_header(t_env *env)
{
	t_content	*data;

	data = env->content;
	if (wof(env->wof, ".name \"%s\"\n.comment \"%s\"\n",
			data->prog_name, data->comment))
		return (-1);
	return (0);
}

int				fill_output(t_env *e)
{
	unsigned int		i;
	char				*ptr;

	ptr = e->content->data;
	if (write_header(e))
		return (-1);
	i = 0;
	while (i < e->size)
	{
		if (ptr[i] >= 1 && ptr[i] <= N_OP)
		{
			if (g_op_tab[ptr[i] - 1].fn(e, ptr, &i, &g_op_tab[ptr[i] - 1]))
				return (-1);
		}
		else
		{
			ft_eprintf("wrong instruction code=%i: EXITING\n", ptr[i]);
			return (-1);
		}
	}
	return (0);
}
