/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_logical.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 15:23:38 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/30 15:23:39 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "msa.h"
#include "wof/wof.h"

int			op_and(t_env *e, char *ptr, unsigned int *offset, const t_op *desc)
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

int			op_or(t_env *e, char *ptr, unsigned int *offset, const t_op *desc)
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

int			op_xor(t_env *e, char *ptr, unsigned int *offset, const t_op *desc)
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
