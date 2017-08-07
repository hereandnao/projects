/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 13:50:07 by saubenne          #+#    #+#             */
/*   Updated: 2016/11/30 12:37:23 by avideau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			get_height(int matrice[4][4])
{
	int width;
	int x;
	int y;
	int block;

	x = 0;
	y = 0;
	width = 0;
	block = 0;
	while (block != 4)
	{
		if (matrice[x][y] == 1)
		{
			block++;
			if (x > width)
				width = x;
		}
		movecount(&x, &y, 4);
	}
	width = width + 1;
	return (width);
}

int			get_width(int matrice[4][4])
{
	int height;
	int x;
	int y;
	int block;

	x = 0;
	y = 0;
	height = 0;
	block = 0;
	while (block != 4)
	{
		if (matrice[x][y] == 1)
		{
			block++;
			if (y > height)
				height = y;
		}
		movecount(&x, &y, 4);
	}
	height = height + 1;
	return (height);
}
