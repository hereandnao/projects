/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hack.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 18:00:39 by bmickael          #+#    #+#             */
/*   Updated: 2017/04/10 18:02:28 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_printf.h"

/*
**	'man 3 stdarg' to understand variadics macro.
*/

int		ft_h_printf(int const fd, const char *restrict format, va_list args)
{
	t_status op;

	ft_memset(&op, 0, sizeof(t_status));
	op.s = format;
	va_copy(op.ap, args);
	new_chain(&op);
	if (op.ptr)
	{
		op.size = write(fd, op.ptr, op.size);
		free(op.ptr);
		return (op.size);
	}
	return (-1);
}
