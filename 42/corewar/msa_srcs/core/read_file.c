/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 21:06:14 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/27 21:06:17 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "msa.h"

static void			*nao_error(t_content *data, char *name, char *s)
{
	free(data);
	ft_eprintf("{red}%s{eoc} -> %s\n", name, s);
	return (NULL);
}

static int			read_init_fd(char *file_name, t_content **file_content)
{
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		ft_eprintf("{red}%s{eoc} -> %s\n", file_name, strerror(errno));
		return (-1);
	}
	if (!(*file_content = (t_content *)ft_memalloc(sizeof(t_content))))
		exit(EXIT_FAILURE);
	return (fd);
}

t_content			*read_file(char *filename, unsigned int *total_size,
																	char *c)
{
	int				fd;
	t_content		*data;
	int				ret;
	int				rest;
	char			*buff;

	if ((fd = read_init_fd(filename, &data)) < 0)
		return (NULL);
	buff = (char *)data;
	rest = FILE_MAX_SIZE;
	while (rest)
	{
		if ((ret = read(fd, buff, rest)) == 0)
			break ;
		if (ret < 0)
			return ((t_content *)nao_error(data, filename, strerror(errno)));
		buff += ret;
		rest -= ret;
	}
	if ((ret = read(fd, c, 1)) != 0)
		return ((t_content *)nao_error(data, filename, "I AM TOO BIG"));
	if (close(fd) < 0)
		return ((t_content *)nao_error(data, filename, strerror(errno)));
	*total_size = FILE_MAX_SIZE - (unsigned int)rest;
	return (data);
}
