/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 13:32:46 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/09 13:32:48 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include "push_swap.h"
#include "get_next_line.h"

static int	count_nb(char *content)
{
	int i;
	int j;
	int nb;

	nb = 0;
	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] != ' ')
		{
			if (j == 0)
				nb++;
			j = 1;
		}
		else
			j = 0;
		i++;
	}
	return (nb);
}

static int	get_content(char *line, t_node **n)
{
	int err;
	int i;

	i = 0;
	while (*line)
	{
		if (*line != ' ')
		{
			push_back(n, ft_special_secure_atoi(line, &err));
			if (err)
			{
				ft_eprintf("ft_special_secure_atoi: Problem detected\n");
				return (0);
			}
			i++;
			while (*line && *line != ' ')
				line++;
		}
		else
			line++;
	}
	return (i);
}

int			read_file(char *name, t_node **n, int *size)
{
	char	*get_line;
	int		fd;
	int		ret;

	if ((fd = open(name, O_RDONLY)) == -1)
	{
		ft_eprintf("push_swap error: problem with file: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if ((ret = get_next_line(fd, &get_line)) == -1)
		exit(EXIT_FAILURE);
	if ((*size = count_nb(get_line)) == 0 ||
											!(ret = get_content(get_line, n))
	|| (ret != *size))
	{
		if (get_line)
			free(get_line);
		ft_eprintf("Bad file format\n");
		return (0);
	}
	if (get_line)
		free(get_line);
	return (1);
}
