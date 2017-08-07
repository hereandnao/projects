/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <saubenne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 10:36:24 by saubenne          #+#    #+#             */
/*   Updated: 2017/07/14 15:31:12 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

void				display_map(char map[4096])
{
	int				i;

	i = 0;
	ft_printf("0x0000 : ");
	while (TRUE)
	{
		ft_printf("%.2hhx ", map[i]);
		i++;
		if (i == 4096)
			break ;
		if (i % 64 == 0)
			ft_printf("\n%#.4x : ", i);
	}
	ft_printf("\n");
}
