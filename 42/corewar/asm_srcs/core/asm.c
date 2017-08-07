/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 22:48:53 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/15 22:48:56 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"

/*
** Upgrade possibles:
** La taille du buffer de sortie peut etre réduite à sizeof(header) +
** len_max_programm + len_max_op				In experience...
** Le programme est suffisement mature pour que get_next_line
** n'ais plus à 'trimer'.
** Plutot que d'utiliser strsplit_trim, on pourrait directement écrire sur
** line et l'utilisee tel quel.
** La fonction l2b(unsigned int a) de common.c ne semble plus utile.
** Il semble que les quelques variables en unsigned short n'ont plus du tout
** besoin de ce type particulier.
*/

static char		*change_extend(char *filename)
{
	char		*tmp;
	char		*output;
	size_t		i;

	i = 0;
	output = NULL;
	if (filename && ((!(tmp = ft_strstr(filename, OLD_SUFFIX)) ||
	((i = (tmp - filename)) + OLD_SUFFIX_SIZE) != ft_strlen(filename))))
		return (NULL);
	if (!(output = (char *)malloc((i + NEW_SUFFIX_SIZE + 1) * sizeof(char))))
		exit(EXIT_FAILURE);
	output[i + NEW_SUFFIX_SIZE] = '\0';
	ft_strncpy(output, filename, i);
	ft_strcpy(output + i, NEW_SUFFIX);
	return (output);
}

static int		create_output_file(t_map *map, size_t buff_size, char *filename)
{
	char		*n_filename;
	int			fd;

	if (!(n_filename = (change_extend(filename))))
	{
		ft_eprintf(ERR_EXTEND);
		return (0);
	}
	if ((fd = open(n_filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR |
											S_IWUSR | S_IRGRP | S_IROTH)) < 0)
	{
		perror(n_filename);
		free(n_filename);
		return (0);
	}
	write(fd, map->buff, buff_size);
	close(fd);
	ft_printf("{green}file saved -> {cyan}%s{eoc}\n", n_filename);
	free(n_filename);
	return (1);
}

static int		parse_file(int fd, t_map *map, size_t *buff_size, int argc)
{
	int			i;
	int			n;
	char		*line;
	t_header	header;

	n = 1;
	ft_bzero(&header, sizeof(header));
	map->ptr = map->buff + sizeof(header);
	while ((i = n_get_trim_line(fd, &line, (map->name && map->comment))) > 0)
	{
		if (!(parse_center(line, &header, map, n++)))
		{
			clear_fd_queue(fd, &line, argc);
			ft_lstdel(&map->label_map, &del_label);
			return (0);
		}
		free(line);
	}
	if (!(manage_label_modifications(map)))
		return (0);
	header.prog_size = l2b((U_INT)(map->ptr - (map->buff + sizeof(header))));
	header.magic = l2b(COREWAR_EXEC_MAGIC);
	*buff_size = map->ptr - map->buff;
	ft_memcpy(map->buff, &header, sizeof(header));
	return (1);
}

static int		open_file(char *filename, int argc)
{
	int			fd;
	t_map		map;
	size_t		buff_size;

	ft_bzero(&map, sizeof(t_map));
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		perror(filename);
		return (0);
	}
	if (!(map.buff = (char *)ft_memalloc((BUFF_SIZE) * sizeof(char))))
		exit(EXIT_FAILURE);
	if (!parse_file(fd, &map, &buff_size, argc) || !debug_result(&map) ||
	!create_output_file(&map, buff_size, filename))
	{
		close(fd);
		free(map.buff);
		return (0);
	}
	free(map.buff);
	close(fd);
	return (1);
}

int				main(int argc, char **argv)
{
	int i;

	if (argc == 1)
	{
		ft_eprintf(ERR_MISSING_FILE);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (++i < argc)
	{
		if (!(open_file(argv[i], argc)))
			ft_eprintf(ERR_SUMARY, argv[i]);
	}
	return (0);
}
