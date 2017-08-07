/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:10:59 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/02 14:11:02 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		ft_free(t_tile **tile, int size_y)
{
	int i;

	i = 0;
	while (i < size_y)
		free(tile[i++]);
	free(tile);
	return (0);
}

static void		init_image(t_env *env)
{
	env->image = mlx_new_image(env->mlx, env->reso_x, env->reso_y);
	env->bpp = 32;
	env->endian = 0;
	env->s_l = env->reso_x * 4;
	env->img_string = mlx_get_data_addr(env->image, &env->bpp, &env->s_l,
																&env->endian);
}

static int		close_win(int keycode, t_env *e)
{
	int			g;
	int			h;
	static int	i = FALSE;

	if (keycode == 53)
	{
		ft_free(e->tile, e->size_y);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 8)
	{
		g = -1;
		while (++g < e->size_y)
		{
			h = 0;
			while (h < e->size_x)
				change_colors(e->frame, &e->tile[g][h++], i);
		}
		draw_all(e, e->tile);
		mlx_put_image_to_window(e->mlx, e->win, e->image, 0, 0);
		i = (i == FALSE) ? TRUE : FALSE;
	}
	else
		ft_printf("Press 'c' to change color or 'esc' to exit\n");
	return (0);
}

static int		init_mlx(t_env *env)
{
	env->reso_x = SCREEN_WIDTH;
	env->reso_y = SCREEN_HEIGHT;
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, env->reso_x, env->reso_y,
		"FDF  -^^,--,~");
	return (1);
}

/*
** init_image(&e);
** mlx_destroy_image(e.mlx, e.image);
*/

int				main(int argc, char **argv)
{
	t_env	e;
	t_frame frame;

	e.frame = &frame;
	if (argc != 2)
	{
		err_printf("%s: Usage : ./fdf <file>\n", argv[0]);
		return (1);
	}
	if (!(e.tile = get_map(argv[1], &e)) || (e.size_x == 1 && e.size_y == 1))
	{
		err_printf("%s: Fatal error\n", argv[0]);
		return (1);
	}
	if (!(init_mlx(&e)))
		return (1);
	init_image(&e);
	ft_bzero(&frame, sizeof(t_frame));
	eval_map(&e, e.tile, &frame);
	assign_coord(&e, e.tile, &frame);
	draw_all(&e, e.tile);
	mlx_put_image_to_window(e.mlx, e.win, e.image, 0, 0);
	mlx_key_hook(e.win, &close_win, &e);
	mlx_loop(e.mlx);
	return (0);
}
