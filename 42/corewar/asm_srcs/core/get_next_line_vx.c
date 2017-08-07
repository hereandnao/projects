/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_vx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 23:02:35 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/15 23:02:38 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** utilisation externe de ft_memmove, ft_memcpy, ft_strchr et ft_bzero.
** ft_strlen n'est pas utilisé ici, on compte sur la cohérance des octets
** lus par read quand à la gestion le l_size AKA l_size && index->b_size AKA
** index->buffer_size.
** Ceci a pour effet d'allonger un tantinet soit peu le code mais evite toutes
** formes de redondance en permettant d'éviter de calculer deux fois
** la même chose, ou d'executer
** des calculs ayant des rapports implicites entres-eux.
** IMPORTANT: Special get_next_line who detect final line whithout \n,
** it return 2 in this case.
*/

#include "get_next_line.h"

static char		*c(char **str, const char *n_buff, size_t *l_size, size_t inc)
{
	char		*new_string;

	if (!(new_string = (char *)malloc((*l_size + inc + 1) * sizeof(char))))
		exit(EXIT_FAILURE);
	new_string[*l_size + inc] = '\0';
	ft_memcpy(new_string, *str, *l_size);
	if (*l_size)
		free(*str);
	*str = new_string;
	ft_memcpy(*str + *l_size, n_buff, inc);
	*l_size += inc;
	return (new_string);
}

/*
** Meaing of 'return ((index->buff_size == 0 && *line) ? 2 : index->buff_size);'
** IMPORTANT: Original get_next_line without
** detecting when no \n present: (index->buff_size == 0 && *line) ? 14
*/

static int		s_exec(t_indexed_buffer *index, char **line)
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
			return ((index->buff_size == 0 && *line) ? 2 : index->buff_size);
		index->buffer[index->buff_size] = '\0';
		if ((jump_location = ft_strchr(index->buffer, '\n')))
			break ;
		if (!c(line, index->buffer, &l_size, index->buff_size))
			return (-1);
		*index->buffer = '\0';
		index->buff_size = 0;
	}
	if (!c(line, index->buffer, &l_size, (i = jump_location - index->buffer)))
		return (-1);
	ft_memmove(index->buffer, jump_location + 1, BUFF_SIZE - (i + 1));
	index->buffer[(index->buff_size -= i + 1)] = '\0';
	return (1);
}

int				n_get_trim_line(int const fd, char **line, int trimed)
{
	static t_indexed_buffer		*index[MAX_DESCRIPTORS];
	int							i;
	char						*tmp;

	if (fd < 0 || fd == 1 || fd == 2 || !line)
		return (-1);
	i = 0;
	while (index[i] != NULL && index[i]->fd != fd && i < MAX_DESCRIPTORS)
		i++;
	if (i == MAX_DESCRIPTORS)
		return (-1);
	if (index[i] == NULL)
	{
		if (!(index[i] = (t_indexed_buffer *)
		ft_memalloc(sizeof(t_indexed_buffer))))
			exit(EXIT_FAILURE);
		index[i]->fd = fd;
	}
	if ((i = s_exec(index[i], (trimed) ? &tmp : line)) > 0 && trimed)
	{
		if (!(*line = ft_strtrim(tmp)))
			exit(EXIT_FAILURE);
		free(tmp);
	}
	return (i);
}

/*
** flush data queuing in fd.
*/

void			clear_fd_queue(int const fd, char **line, int argc)
{
	free(*line);
	if (argc <= 2)
		return ;
	while (n_get_trim_line(fd, line, FALSE))
		free(*line);
}
