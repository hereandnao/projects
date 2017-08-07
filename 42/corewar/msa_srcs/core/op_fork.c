/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 15:23:59 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/30 15:24:01 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "msa.h"
#include "wof/wof.h"

int		op_fork(t_env *e, char *ptr, unsigned int *offset, const t_op *desc)
{
	int				output;

	*offset += 1;
	output = ptr[*offset] & 0xff;
	*offset += 1;
	output <<= 8;
	output += ptr[*offset] & 0xff;
	*offset += 1;
	output = (short int)output;
	if (wof(e->wof, "%s %%%hi", desc->name, output))
		return (-1);
	return (0);
}

int		op_lfork(t_env *e, char *ptr, unsigned int *offset, const t_op *desc)
{
	int				output;

	*offset += 1;
	output = ptr[*offset] & 0xff;
	*offset += 1;
	output <<= 8;
	output += ptr[*offset] & 0xff;
	*offset += 1;
	output = (short int)output;
	if (wof(e->wof, "%s %%%hi", desc->name, output))
		return (-1);
	return (0);
}
