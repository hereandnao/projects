/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avideau <avideau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 14:28:42 by avideau           #+#    #+#             */
/*   Updated: 2016/11/30 12:41:37 by avideau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int				main(int argc, char **argv)
{
	t_list		*lst;
	char		**result;
	int			size;

	lst = NULL;
	if (argc != 2)
		ft_putstr("usage: fillit input_file\n");
	else
	{
		if ((lst = readmap(argv[1])) != '\0')
		{
			size = calcul_min_size(lst_size(lst));
			result = test_pose(lst, &size);
			print_matrice(result, size);
			free_matrice(result, size);
			ft_lstdel(&lst);
			return (1);
		}
		ft_putstr("error\n");
		return (0);
	}
	return (0);
}

void			free_matrice(char **result, int size)
{
	int y;

	y = 0;
	while (y < size)
	{
		free(result[y]);
		result[y] = NULL;
		y++;
	}
	free(result);
	result = NULL;
}

char			**test_pose(t_list *lst, int *size)
{
	char	**result;

	result = new_matrice(*size);
	if (tetris_solve(*size, result, lst))
		return (result);
	else
	{
		free_matrice(result, *size);
		*size = *size + 1;
		return (test_pose(lst, &*size));
	}
}
