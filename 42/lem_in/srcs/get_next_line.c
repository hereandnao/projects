/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 01:37:54 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/09 18:40:21 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "lemin.h"

static char		*s_concat(char **str, const char *buff, size_t *l, size_t n)
{
	char *output;

	if (!(output = (char *)malloc((*l + n + 1) * sizeof(char))))
		return (NULL);
	output[*l + n] = '\0';
	ft_memcpy(output, *str, *l);
	if (*l)
		free(*str);
	*str = output;
	ft_memcpy(*str + *l, buff, n);
	*l += n;
	return (output);
}

static int		s_exec(t_buffer *index, char **line)
{
	char		*jump_location;
	size_t		l_size;
	size_t		i;

	*line = NULL;
	l_size = 0;
	while (TRUE)
	{
		if ((index->buff_size < 1) &&
		(index->buff_size = read(index->fd, index->buffer, BUFF_SIZE)) <= 0)
			return ((index->buff_size == 0 && *line) ? 1 : index->buff_size);
		index->buffer[index->buff_size] = '\0';
		if ((jump_location = ft_strchr(index->buffer, '\n')))
			break ;
		if (!s_concat(line, index->buffer, &l_size, index->buff_size))
			return (-1);
		*index->buffer = '\0';
		index->buff_size = 0;
	}
	if (!s_concat(line, index->buffer, &l_size,
		(i = jump_location - index->buffer)))
		return (-1);
	ft_memmove(index->buffer, jump_location + 1, BUFF_SIZE - (i + 1));
	index->buffer[(index->buff_size -= i + 1)] = '\0';
	return (1);
}

static char		*swiss_add_line(char *s1, char *s2, int *n)
{
	char	*output;
	size_t	len1;
	size_t	len2;
	size_t	i;

	(*n)++;
	len1 = (s1) ? ft_strlen(s1) : 0;
	len2 = ft_strlen(s2);
	i = len1 + len2;
	if (!(output = (char *)malloc((i + 2) * sizeof(char))))
		return (NULL);
	ft_strncpy(output, s1, len1);
	ft_strncpy(output + len1, s2, len2);
	output[i] = '\n';
	output[i + 1] = '\0';
	free(s1);
	return (output);
}

int				get_next_line(const int fd, char **line)
{
	static t_buffer	*index[MAX_DESCRIPTORS];
	int				i;

	if (fd < 0 || fd == 1 || fd == 2 || !line)
		return (-1);
	i = 0;
	while (index[i] != NULL && index[i]->fd != fd && i < MAX_DESCRIPTORS)
		i++;
	if (i == MAX_DESCRIPTORS)
		return (-1);
	if (index[i] == NULL)
	{
		if (!(index[i] = (t_buffer *)malloc(sizeof(t_buffer))))
			return (-1);
		ft_bzero(index[i]->buffer, BUFF_SIZE + 1);
		index[i]->buff_size = 0;
		index[i]->fd = fd;
	}
	return (s_exec(index[i], line));
}

int				swiss_line(const int fd, char **line, t_swiss p, char *needdle)
{
	char	*tmp;
	int		i;
	int		n;

	*line = NULL;
	while (p.a-- > 0)
	{
		if ((i = get_next_line(fd, &tmp)) <= 0)
			return (i);
		free(tmp);
	}
	n = 0;
	while (p.b-- > 0)
	{
		if ((i = get_next_line(fd, &tmp)) < 0)
			return (i);
		if (i != 0 && (!needdle || ft_strstr(tmp, needdle)))
			if (!(*line = swiss_add_line(*line, tmp, &n)))
				return (-1);
		if (tmp)
			free(tmp);
	}
	if (*line && (tmp = ft_strrchr(*line, '\n')))
		*tmp = '\0';
	return ((*line) ? n : 0);
}
