/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:12:24 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/02 14:12:31 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			change_colors(t_frame *f, t_tile *t, int state)
{
	float	r_diff;
	float	g_diff;
	float	b_diff;
	float	ratio;

	if (state == TRUE)
	{
		ratio = (t->z - f->z_min) / (f->z_max - f->z_min);
		r_diff = (COLOR_MAX >> 16) - (COLOR_MIN >> 16);
		g_diff = ((COLOR_MAX >> 8) & 0xFF) - ((COLOR_MIN >> 8) & 0xFF);
		b_diff = (COLOR_MAX & 0xFF) - (COLOR_MIN & 0xFF);
		t->color = (int)((((COLOR_MIN >> 16) + ((int)(ratio * r_diff))) << 16) |
					((((COLOR_MIN >> 8) & 0xFF) + (int)(ratio * g_diff)) << 8) |
					((COLOR_MIN & 0xFF) + (int)(ratio * b_diff)));
	}
	else
		t->color = t->defined_color;
}

static void		set_line(t_line *line, t_tile tile)
{
	line->x2 = tile.x;
	line->y2 = tile.y;
	line->f_color = tile.color;
}

void			draw_all(t_env *env, t_tile **tile)
{
	t_line		line;
	int			g;
	int			h;

	g = -1;
	while (++g < env->size_y)
	{
		h = -1;
		while (++h < env->size_x)
		{
			line.x1 = tile[g][h].x;
			line.y1 = tile[g][h].y;
			line.b_color = tile[g][h].color;
			if (h != (env->size_x - 1))
			{
				set_line(&line, tile[g][h + 1]);
				draw_line(env, &line);
			}
			if (g != (env->size_y - 1))
			{
				set_line(&line, tile[g + 1][h]);
				draw_line(env, &line);
			}
		}
	}
}

void			assign_coord(t_env *env, t_tile **tile, t_frame *f)
{
	int g;
	int h;

	g = 0;
	while (g < env->size_y)
	{
		h = 0;
		while (h < env->size_x)
		{
			tile[g][h].x = f->offset_x + ((g + h) * f->tile_width);
			tile[g][h].y = f->offset_y + ((g - h) * f->tile_height) -
												(tile[g][h].z * f->ratio_z);
			change_colors(f, &tile[g][h], TRUE);
			h++;
		}
		g++;
	}
}
