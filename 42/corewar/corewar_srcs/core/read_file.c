/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 22:10:54 by saubenne          #+#    #+#             */
/*   Updated: 2017/07/24 22:10:58 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "libft.h"
#include "vm.h"

static void			*nao_error(t_warrior *data, char *name, char *s)
{
	free(data);
	ft_eprintf("{red}%s{eoc} -> %s\n", name, s);
	return (NULL);
}

static int			read_init_fd(char *file_name, t_warrior **data)
{
	int		fd;

	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		ft_eprintf("{red}%s{eoc} -> %s\n", file_name, strerror(errno));
		return (-1);
	}
	if (!(*data = (t_warrior *)ft_memalloc(sizeof(t_warrior))))
		exit(EXIT_FAILURE);
	return (fd);
}

t_warrior			*read_file(char *file_name, unsigned int *total_size,
																	char *c)
{
	int				fd;
	t_warrior		*data;
	int				ret;
	int				rest;
	char			*buff;

	if ((fd = read_init_fd(file_name, &data)) < 0)
		return (NULL);
	buff = (char *)data;
	rest = FILE_MAX_SIZE;
	while (rest)
	{
		if ((ret = read(fd, buff, rest)) == 0)
			break ;
		if (ret < 0)
			return ((t_warrior *)nao_error(data, file_name, strerror(errno)));
		buff += ret;
		rest -= ret;
	}
	if ((ret = read(fd, c, 1)) != 0)
		return ((t_warrior *)nao_error(data, file_name, "I AM TOO BIG"));
	if (check_file(&data->file) || close(fd) < 0)
		return ((t_warrior *)nao_error(data, file_name, "bad cor file"));
	*total_size = FILE_MAX_SIZE - (unsigned int)rest;
	return (data);
}
