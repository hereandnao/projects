/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 17:15:28 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/18 17:04:05 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		g_next_line(int const fd, char **line, char *buf)
{
	int					ret;
	char				*eol;
	unsigned long int	i;

	*line = NULL;
	ret = 0;
	while ((i = ft_strlen(buf)) > 0
	|| (ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (ret)
			buf[ret] = '\0';
		if (!(eol = ft_strchr(buf, '\n')))
		{
			*line = ft_strnjoin(*line, buf, (ret) ? ret : i);
			ft_bzero(buf, (ret) ? BUFF_SIZE : i);
		}
		else
		{
			*eol = '\0';
			*line = ft_strnjoin(*line, buf, eol - buf);
			ft_memmove(buf, eol + 1, BUFF_SIZE - (eol - buf - 1));
			return (1);
		}
	}
	return ((ret == 0 && *line) ? 1 : ret);
}

int				get_next_line(int const fd, char **line)
{
	static char *table[4864];

	if (fd > 4864 || fd < 0 || !line)
		return (-1);
	if (table[fd] == NULL)
		table[fd] = ft_memalloc(BUFF_SIZE + 1);
	return (g_next_line(fd, line, table[fd]));
}

int				find_word(int const fd, char **line, char *needle)
{
	char *str;

	str = NULL;
	if (fd < 0 || !line)
		return (-1);
	if (!needle)
		return (0);
	while (get_next_line(fd, line) == 1)
	{
		str = ft_strstr(*line, needle);
		if (str != NULL)
			break ;
		else
			free(*line);
	}
	if (str == NULL)
		return (0);
	return (1);
}
