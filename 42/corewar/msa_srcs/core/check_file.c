/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 13:33:15 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/30 13:33:16 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "msa.h"

/*
** On ne tolere pas l'absence de commentaire et encore moins de nom de champion.
** la taille d'un commentaire ou d'un nom de champion doit etre inferieure ou
** egale a PROG_NAME_LENGTH et COMMENT_LENGTH.
*/

static int		check_length(char *ptr, int max_length, int tolerance)
{
	int		i;
	int		j;

	i = 0;
	while (i < (max_length + 4))
	{
		if (ptr[i] == '\0')
			break ;
		i++;
	}
	j = i;
	while (j < (max_length + 4))
	{
		if (ptr[j] != '\0')
			return (-1);
		j++;
	}
	return ((i != tolerance && i <= max_length) ? 0 : -1);
}

static int		check_magic(unsigned char magic[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (magic[i] != (COREWAR_EXEC_MAGIC >> (24 - (i * 8)) & 0xff))
		{
			ft_eprintf("ERROR : Wrong Magic number !\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int				check_file(t_content *data)
{
	if (check_length(data->prog_name, PROG_NAME_LENGTH, 0) < 0)
	{
		ft_eprintf("bad size of champion name !\n");
		return (-1);
	}
	if (check_length(data->comment, COMMENT_LENGTH, -1) < 0)
	{
		ft_eprintf("bad size of comment !\n");
		return (-1);
	}
	if (check_magic(data->magic))
		return (-1);
	return (0);
}
