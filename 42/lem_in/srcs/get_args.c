/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:36:28 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/23 17:05:46 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		assign_flags(char *s, t_opts *flags)
{
	while (*s)
	{
		if (*s == 'v')
			*flags |= VERBOSE;
		else if (*s == 'f')
			*flags |= READ_FILE;
		else
			return ((int)*s);
		s++;
	}
	return (0);
}

static int		open_file(char *filename)
{
	int		fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		ft_eprintf("Error: couldn't open file: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static void		error_msg(char *cmd, char letter)
{
	ft_eprintf("%s : illegal option -- %c\nusage: %s [-v] [...] || [-f]\
[Input file]\n", cmd, letter, cmd, 2);
	exit(EXIT_FAILURE);
}

int				get_nao(int argc, char **argv, t_map *map)
{
	int			i;
	int			err;

	i = 0;
	while (++i < argc)
	{
		if (*argv[i] == '-')
		{
			if (ft_strlen(argv[i]) < 2)
				error_msg(argv[0], *argv[i]);
			if ((err = assign_flags(argv[i] + 1, &map->flags)))
				error_msg(argv[0], (char)err);
		}
		else
			break ;
	}
	if (map->flags & READ_FILE)
		return (open_file(argv[i++]));
	if (i != argc)
		error_msg(argv[0], ' ');
	return (0);
}
