/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bytecode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 15:23:10 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/30 15:23:12 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "msa.h"
#include "wof/wof.h"

static int			verif(unsigned char nb, const t_op *g, unsigned int *offset,
																		int i)
{
	int				res;

	while (++i < g->param_nb)
		if ((res = (nb >> (6 - (2 * i))) & 0b11) == REG_CODE)
		{
			*offset += 1;
			if (!(g->naocode[i] & T_REG))
				return (-1);
		}
		else if (res == DIR_CODE)
		{
			*offset += (g->v_size) ? 2 : 4;
			if (!(g->naocode[i] & T_DIR))
				return (-1);
		}
		else if (res == IND_CODE)
		{
			*offset += 2;
			if (!(g->naocode[i] & T_IND))
				return (-1);
		}
		else
			return (-1);
	return (0);
}

int					check_bytecode(t_env *e, char *ptr, unsigned int l,

															const t_op *desc)
{
	unsigned int	len;
	int				i;

	len = 1;
	i = -1;
	if (verif((unsigned char)ptr[l], desc, &len, i) == -1)
	{
		ft_printf("Invalid Bytecode\n");
		return (-1);
	}
	if ((len + l) > e->size)
	{
		ft_eprintf("Error : wrong size\n");
		return (-1);
	}
	return (0);
}
