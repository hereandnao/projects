/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 15:23:16 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/30 15:23:17 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "msa.h"
#include "wof/wof.h"

static int	get_nb(char *bf, int pc)
{
	int			res;

	res = (bf[pc]) & 0xff;
	res <<= 8;
	res |= (bf[(pc + 1)]) & 0xff;
	res <<= 8;
	res |= (bf[(pc + 2)]) & 0xff;
	res <<= 8;
	res |= (bf[(pc + 3)]) & 0xff;
	return (res);
}

int			op_live(t_env *e, char *ptr, unsigned int *offset, const t_op *desc)
{
	int nb;

	*offset += 1;
	nb = get_nb(ptr, (*offset));
	if (wof(e->wof, "%s %%%d", desc->name, nb))
		return (-1);
	*offset += 4;
	if (*offset > e->size)
		return (-1);
	return (0);
}

int			op_zjmp(t_env *e, char *ptr, unsigned int *offset, const t_op *desc)
{
	int nb;

	*offset += 1;
	nb = ptr[*offset] & 0xff;
	*offset += 1;
	nb <<= 8;
	nb |= ptr[*offset] & 0xFF;
	if (wof(e->wof, "%s %%%hd", desc->name, nb))
		return (-1);
	*offset += 1;
	if (*offset > e->size)
		return (-1);
	return (0);
}

int			op_aff(t_env *e, char *ptr, unsigned int *offset, const t_op *desc)
{
	if (put(e->wof, "%s", desc->name))
		return (-1);
	*offset += 1;
	if (check_bytecode(e, ptr, *offset, desc) == -1)
		return (-1);
	if (extractor(e, ptr, offset, desc) == -1)
		return (-1);
	if (put(e->wof, "\n"))
		return (-1);
	return (0);
}
