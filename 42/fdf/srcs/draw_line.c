/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:11:07 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/02 14:11:14 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** ft_printf("r_diff = %hhx\n", r_diff);
** ft_printf("g_diff = %hhx\n", g_diff);
** ft_printf("b_diff = %hhx\n", b_diff);
** ft_printf("ratio = %f\n", ratio);
** ft_printf("color = %#.2x\n", (int)(ratio * r_diff));
*/

static void		fill_pixel(t_env *env, int x, int y, int color)
{
	int offset;

	offset = (y * env->reso_x * 4) + (x * 4);
	if (offset >= (env->reso_x * env->reso_y * 4) || offset < 0)
		return ;
	env->img_string[offset] = color & 0xFF;
	env->img_string[offset + 1] = (color >> 8) & 0xFF;
	env->img_string[offset + 2] = (color >> 16) & 0xFF;
	env->img_string[offset + 3] = (color >> 24) & 0xFF;
}

static int		get_color(t_line *p, float x, float x_beg, float x_end)
{
	int		color;
	float	r_diff;
	float	g_diff;
	float	b_diff;
	float	ratio;

	ratio = (x - x_beg) / (x_end - x_beg);
	r_diff = (p->f_color >> 16) - (p->b_color >> 16);
	g_diff = ((p->f_color >> 8) & 0xFF) - ((p->b_color >> 8) & 0xFF);
	b_diff = (p->f_color & 0xFF) - (p->b_color & 0xFF);
	color = ((((p->b_color >> 16) + ((int)(ratio * r_diff))) << 16) |
			((((p->b_color >> 8) & 0xFF) + (int)(ratio * g_diff)) << 8) |
			((p->b_color & 0xFF) + (int)(ratio * b_diff)));
	return (color);
}

static void		horizontal_line(t_env *env, t_line *p, int x_inc, int y_inc)
{
	int cumul;
	int x;
	int y;
	int color;

	cumul = p->dx / 2;
	x = p->x1;
	y = p->y1;
	while (TRUE)
	{
		x += x_inc;
		cumul += p->dy;
		if (cumul >= p->dx)
		{
			y += y_inc;
			cumul -= p->dx;
		}
		color = get_color(p, x, p->x1, p->x2);
		fill_pixel(env, x, y, color);
		if (x == p->x2)
			break ;
	}
}

static void		vertical_line(t_env *env, t_line *p, int x_inc, int y_inc)
{
	int cumul;
	int x;
	int y;
	int color;

	cumul = p->dy / 2;
	x = p->x1;
	y = p->y1;
	while (TRUE)
	{
		y += y_inc;
		cumul += p->dx;
		if (cumul >= p->dy)
		{
			x += x_inc;
			cumul -= p->dy;
		}
		color = get_color(p, y, p->y1, p->y2);
		fill_pixel(env, x, y, color);
		if (y == p->y2)
			break ;
	}
}

void			draw_line(t_env *env, t_line *p)
{
	int x_inc;
	int y_inc;

	p->dx = p->x2 - p->x1;
	p->dy = p->y2 - p->y1;
	x_inc = (p->dx < 0) ? -1 : 1;
	y_inc = (p->dy < 0) ? -1 : 1;
	p->dx = abs(p->dx);
	p->dy = abs(p->dy);
	fill_pixel(env, p->x1, p->y1, p->b_color);
	if (p->dx == 0 && p->dy == 0)
		return ;
	if (p->dx > p->dy)
		horizontal_line(env, p, x_inc, y_inc);
	else
		vertical_line(env, p, x_inc, y_inc);
}
