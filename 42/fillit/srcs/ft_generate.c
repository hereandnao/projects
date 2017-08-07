/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avideau <avideau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:32:52 by avideau           #+#    #+#             */
/*   Updated: 2016/11/30 12:37:16 by avideau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char		**new_matrice(int size)
{
	t_map	count;
	char	**matrice;

	count.x = 0;
	count.y = 0;
	if (!(matrice = (char **)malloc(size * sizeof(*matrice))))
		return (0);
	while (count.y < size)
	{
		if (count.y == 0)
		{
			if (!(matrice[count.x] = (char*)malloc(size * sizeof(*matrice))))
				return (0);
		}
		matrice[count.x][count.y] = '.';
		movecount(&count.x, &count.y, size);
	}
	return (matrice);
}

void		movecount(int *x, int *y, int size)
{
	*x = *x + 1;
	if (*x == size)
	{
		*x = 0;
		*y = *y + 1;
	}
}
