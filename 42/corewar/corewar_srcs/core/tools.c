/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 13:21:43 by bmickael          #+#    #+#             */
/*   Updated: 2017/06/28 13:22:04 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

unsigned int		get_real_size(char prog_size[4])
{
	int				i;
	unsigned int	res;

	i = 0;
	res = 0;
	while (i < 4)
	{
		res <<= 8;
		res |= (prog_size[i] & 0xff);
		i++;
	}
	return (res);
}

void				champ_debug(t_list *lst, t_env *e)
{
	t_champ_num		*c;

	while (lst)
	{
		c = lst->content;
		ft_printf("champion %s nb %i\n", c->name, c->nb);
		lst = lst->next;
	}
	ft_printf("VERBOSE = %i\nGRAPHIC = %i\nDUMP = %i\ndump value = %i\n",
			(e->flags & VERBOSE), (e->flags & GRAPHIC), (e->flags & DUMP),
			e->dump_value);
}

t_list				*err_bad_size(t_list *lst)
{
	ft_printf("ERROR: Real size and file size dont match !\n");
	free_t_list(lst);
	return (NULL);
}

/*
** since reg[0] = r1, reg = n -1
** check if 0 <= reg < 16
*/

int					get_reg_value(char *bf, t_process *process, int *offset,
																int *error)
{
	int				n;

	*error = FALSE;
	n = bf[(process->pc + *offset) & MEM_MASK];
	n &= 0xff;
	n -= 1;
	(*offset)++;
	if (!(n < REG_NUMBER && n >= 0))
	{
		*error = TRUE;
		return (0);
	}
	return (process->reg[n]);
}
