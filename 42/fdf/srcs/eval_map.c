/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:11:26 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/02 14:11:28 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			get_tmp_var(t_env *env, t_tile tile, t_frame *f)
{
	int tmp_min;
	int tmp_max;

	tmp_min = ((0 - (env->size_x - 1)) * f->tile_height) -
											(tile.z * f->ratio_z);
	tmp_max = ((env->size_y - 1) * f->tile_height) - (tile.z * f->ratio_z);
	if (tile.z < f->z_min)
		f->z_min = tile.z;
	if (tile.z > f->z_max)
		f->z_max = tile.z;
	if (tmp_min < f->y_min)
		f->y_min = tmp_min;
	if (tmp_max > f->y_max)
		f->y_max = tmp_max;
}

/*
** float	x_max;
** x_max = ((e->size_y - 1) + (e->size_x - 1)) * f->tile_width;
** f->offset_x = (e->reso_x - x_map) / 2
*/

void				eval_map(t_env *e, t_tile **tile, t_frame *f)
{
	float	ecart_type;
	int		g;
	int		h;

	f->tile_width = (e->reso_x - 20) / ((e->size_y - 1) + (e->size_x - 1));
	f->tile_height = f->tile_width / 2;
	f->offset_x = (e->reso_x - (float)(((e->size_y - 1) + (e->size_x - 1))
														* f->tile_width)) / 2;
	f->ratio_z = RATIO_Z;
	ecart_type = e->reso_y + 1;
	while (ecart_type > e->reso_y && f->ratio_z > 0.0000001)
	{
		f->ratio_z = (f->ratio_z > 1) ? f->ratio_z - 1 : f->ratio_z / 2;
		f->y_min = 0;
		f->y_max = 0;
		g = -1;
		while (++g < e->size_y)
		{
			h = -1;
			while (++h < e->size_x)
				get_tmp_var(e, tile[g][h], f);
		}
		ecart_type = f->y_max - f->y_min;
	}
	f->offset_y = (e->reso_y / 2) - ((f->y_max + f->y_min) / 2);
}
