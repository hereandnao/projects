/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
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

static int			get_reg(t_env *e, char *bf, unsigned int *offset)
{
	int				n;

	n = bf[*offset];
	n &= 0xff;
	if (!(n <= REG_NUMBER && n > 0))
	{
		ft_eprintf("Bad register value ! Have %i\n", n);
		return (-1);
	}
	if (put(e->wof, " r%i", n))
		return (-1);
	(*offset)++;
	return (n);
}

/*
** TODO En cas de v_size, le cast en %hi est-il bon a faire ?
*/

static int			extract_dir(t_env *e, char *field, unsigned int *offset,
																	int v_size)
{
	int				output;
	int				i;

	i = *offset;
	*offset += (v_size) ? 2 : 4;
	output = field[i] & 0xff;
	output = (output << 8) + (field[++i] & 0xff);
	if (v_size)
	{
		output = (short int)output;
		if (put(e->wof, " %%%hi", output))
			return (-1);
		return (0);
	}
	output = (output << 8) + (field[++i] & 0xff);
	output = (output << 8) + (field[++i] & 0xff);
	if (put(e->wof, " %%%i", output))
		return (-1);
	return (0);
}

static int			extract_ind(t_env *e, char *field, unsigned int *offset)
{
	int				output;

	output = field[*offset] & 0xff;
	(*offset)++;
	output = (output << 8) + (field[*offset] & 0xff);
	(*offset)++;
	if (put(e->wof, " %hi", output))
		return (-1);
	return (0);
}

int					extractor(t_env *e, char *ptr, unsigned int *offset,
															const t_op *desc)
{
	unsigned char	nb;
	int				res;
	int				i;

	nb = ptr[*offset];
	*offset += 1;
	i = -1;
	while (++i < desc->param_nb)
	{
		if (i != 0 && put(e->wof, ","))
			return (-1);
		res = (nb >> (6 - (2 * i))) & 0b11;
		if (res == 0b01)
		{
			if (get_reg(e, ptr, offset) < 0)
				return (-1);
		}
		else if (res == 0b10 && extract_dir(e, ptr, offset, desc->v_size))
			return (-1);
		else if (res == 0b11 && extract_ind(e, ptr, offset))
			return (-1);
	}
	return (0);
}
