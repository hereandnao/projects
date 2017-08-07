/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 15:44:25 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/23 15:44:29 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"
# include "mlx.h"
# include <limits.h>

# define SCREEN_WIDTH	1920
# define SCREEN_HEIGHT	1080

# define HEX		"0123456789ABCDEF"

# define RATIO_Z	12

# define WHITE		0x00FFFFFF
# define RED		0x00FF0000
# define GREEN 		0x0000FF00
# define BLUE		0x000000FF
# define PURPLE		0x00FF00FF
# define YELLOW		0x00FFFF00
# define ORANGE		0x00FFA500

# define COLOR_MIN	0x00FF88
# define COLOR_MAX	0xFF00FF

typedef struct		s_tile
{
	int	x;
	int y;
	int z;
	int color;
	int defined_color;
}					t_tile;

typedef struct		s_frame
{
	float			tile_width;
	float			tile_height;
	int				offset_x;
	int				offset_y;
	int				y_min;
	int				y_max;
	float			z_min;
	float			z_max;
	float			ratio_z;
}					t_frame;

typedef	struct		s_env
{
	void			*mlx;
	void			*win;
	float			reso_x;
	float			reso_y;
	int				size_x;
	int				size_y;
	void			*image;
	char			*img_string;
	int				s_l;
	int				bpp;
	int				endian;
	t_tile			**tile;
	t_frame			*frame;
}					t_env;

typedef struct		s_line
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	int				dx;
	int				dy;
	int				b_color;
	int				f_color;
}					t_line;

void				eval_map(t_env *env, t_tile **tile, t_frame *frame);
void				assign_coord(t_env *env, t_tile **tile, t_frame *f);
void				draw_all(t_env *e, t_tile **tile);
t_tile				**get_map(char *file, t_env *env);
void				ft_secure_atoi(const char *nptr, int *error, t_tile *tile);
void				draw_line(t_env *env, t_line *p);
int					ft_push_front(t_list **alst, void *data, size_t size);
void				ft_listinvert(t_list **alst);
int					count_nb(char *content);
void				change_colors(t_frame *f, t_tile *t, int state);

#endif
