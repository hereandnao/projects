/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 23:13:36 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/15 23:13:40 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"

/*
**  rX => REGISTER
**  % => DIRECT
** (other) => INDIRECT
*/

static char			*set_reg(char *content, t_map *map, t_op *op, int n)
{
	int i;
	int error;

	if (n > (op->n_params - 1) || (!(op->params[n] & T_REG)))
		return (ERR_PARAM_CKECK);
	i = secure_atoi(content + 1, &error);
	if (error || i < 1 || i > 16)
		return (ERR_REG);
	*(map->ptr)++ = i;
	return (NULL);
}

static char			*set_dir(char *content, t_map *map, t_op *op, int n)
{
	int				i;
	int				error;
	int				size;
	char			*err;

	if (n > (op->n_params - 1) || (!(op->params[n] & T_DIR)))
		return (ERR_PARAM_CKECK);
	content += 1;
	error = 0;
	size = (op->v_size) ? 2 : 4;
	if (*content != ':')
	{
		i = secure_atoi(content, &error);
		if (error)
			return (ERR_ATOI);
		write_direct_value(map->ptr, i, size);
		map->ptr += size;
		return (NULL);
	}
	if ((err = assign_label_jump(content + 1, map, size)))
		return (err);
	map->ptr += size;
	return (NULL);
}

static char			*set_ind(char *content, t_map *map, t_op *op, int n)
{
	int				i;
	int				error;
	int				size;
	char			*err;

	if (n > (op->n_params - 1) || (!(op->params[n] & T_IND)))
		return (ERR_PARAM_CKECK);
	error = 0;
	size = (op->v_size) ? 2 : 2;
	if (*content != ':')
	{
		i = secure_atoi(content, &error);
		if (error)
			return (ERR_ATOI);
		write_direct_value(map->ptr, i, size);
		map->ptr += size;
		return (NULL);
	}
	if ((err = assign_label_jump(content + 1, map, size)))
		return (err);
	map->ptr += size;
	return (NULL);
}

static t_fn g_fn[3] = {
	{ 'r', &set_reg, REG_CODE },
	{ '%', &set_dir, DIR_CODE },
	{ ' ', &set_ind, IND_CODE }
};

static void			update_flag(char *location, char flag)
{
	unsigned char	mask;
	int				offset;

	offset = 6;
	mask = 0b11000000;
	while (mask != 0x00)
	{
		if (!(*location & mask))
		{
			*location |= (flag << offset);
			break ;
		}
		offset -= 2;
		mask = mask >> 2;
	}
}

/*
** older vesion: return (ERR_SPLIT);
** now: exit(EXIT_FAILURE);
*/

char				*write_instruction(char *line, t_op *op, t_map *map)
{
	char			**content;
	int				size;
	int				i;
	int				j;
	char			*err;

	if (!(content = trim_strsplit(line, ',', &size)))
		exit(EXIT_FAILURE);
	if (size != op->n_params)
		return (clean_content_memory(content, ERR_N_PARAMS));
	map->origin_op = map->ptr++;
	*(map->origin_op) = op->i;
	map->ptr += (op->o_code) ? 1 : 0;
	i = -1;
	while (content[++i])
	{
		j = -1;
		while ((content[i][0] != g_fn[++j].l && j != 2))
			;
		if ((err = (g_fn[j].f(content[i], map, op, i))))
			return (clean_content_memory(content, err));
		if (op->o_code)
			update_flag(map->origin_op + 1, g_fn[j].flag);
	}
	return (clean_content_memory(content, NULL));
}
