/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <saubenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:09:42 by saubenne          #+#    #+#             */
/*   Updated: 2016/11/30 12:44:14 by avideau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		print_matrice(char **matrice, int size)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y != size)
	{
		ft_putchar((matrice[x][y] == '0') ? '.' : matrice[x][y]);
		if (++x == size)
		{
			x = 0;
			y++;
			ft_putchar('\n');
		}
	}
}
