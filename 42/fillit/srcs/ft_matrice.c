/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avideau <avideau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 14:28:42 by avideau           #+#    #+#             */
/*   Updated: 2016/11/30 12:37:30 by avideau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int				getmin_col(int matrice[4][4])
{
	int min_col;
	int foundbout;
	int x;
	int y;

	min_col = 3;
	foundbout = 0;
	x = 0;
	y = 0;
	while (foundbout != 4 && min_col != 0)
	{
		if (matrice[x][y] == 1)
		{
			foundbout++;
			if (min_col > x)
				min_col = x;
		}
		x++;
		if (x == 4)
		{
			x = 0;
			y++;
		}
	}
	return (min_col);
}

void			moveto_origin(int matrice[4][4])
{
	int	min_col;
	int	x;
	int	y;
	int	min_line;

	min_col = getmin_col(matrice);
	x = 0;
	y = 0;
	min_line = -1;
	while (y != 4)
	{
		if (matrice[x][y] == 1)
		{
			if (min_line < 0)
				min_line = y;
			matrice[x][y] = 0;
			matrice[x - min_col][y - min_line] = 1;
		}
		x++;
		if (x == 4)
		{
			x = 0;
			y++;
		}
	}
}
