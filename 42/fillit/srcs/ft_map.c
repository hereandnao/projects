/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avideau <avideau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 14:59:15 by avideau           #+#    #+#             */
/*   Updated: 2016/11/30 14:21:23 by avideau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_list			*readmap(char *file)
{
	t_read	rd_file;
	int		i;
	int		end;
	t_list	*new;

	new = NULL;
	i = 0;
	end = 0;
	if ((rd_file.fd = open(file, O_RDONLY)) == -1)
		return (0);
	while ((rd_file.ret = read(rd_file.fd, rd_file.buf, 21)))
	{
		rd_file.buf[rd_file.ret] = '\0';
		end = end + check_map(rd_file.buf);
		if (!check_conditions(rd_file.buf, i) ||
				!lst_add(&new, lstnew_tetris(rd_file.buf, i++)))
			return (0);
	}
	if (close(rd_file.fd) == -1 || ((i * 5) - 1 == end) ? 0 : 1)
		return (0);
	if (new != NULL)
		return (new);
	return (0);
}

int				check_conditions(char *buf, int i)
{
	if (!buf)
		return (0);
	return ((i >= 26 || check_map(buf) == 0 || check_tet_connex(buf) == 0 ||
				check_tetris(buf) == 0) ? 0 : 1);
}

int				check_tetris(char *buf)
{
	int if_tet;
	int spaces;
	int i;

	i = -1;
	if_tet = 0;
	spaces = 0;
	while (buf[++i])
	{
		if (if_tet == 0 && buf[i] == '#' && (i++))
		{
			if_tet = 1;
			spaces = 0;
		}
		if (if_tet == 1 && buf[i] != '#')
		{
			if (buf[i + 1] == '#')
				return (0);
			if_tet = 0;
			spaces++;
		}
		if (spaces > 4)
			return (0);
	}
	return (1);
}

int				check_tet_connex(char *buf)
{
	int i;
	int connex;

	connex = 0;
	i = 0;
	while (i < 20)
	{
		if (buf[i] == '#')
		{
			if (((i + 1) <= 20 ? buf[i + 1] : '.') == '#' && (i + 1) < 20)
				connex++;
			if (((i + 5) <= 20 ? buf[i + 5] : '.') == '#' && (i + 5) < 20)
				connex++;
			if (((i - 1) >= 0 ? buf[i - 1] : '.') == '#' && (i - 1) >= 0)
				connex++;
			if (((i - 5) >= 0 ? buf[i - 5] : '.') == '#' && (i - 5) >= 0)
				connex++;
		}
		i++;
	}
	if (connex == 6 || connex == 8)
		return (1);
	else
		return (0);
}

int				check_map(char *buf)
{
	int count_tetris;
	int count_retour;
	int count;
	int i;

	count = 0;
	count_retour = 0;
	count_tetris = 0;
	i = 0;
	while (buf[i])
	{
		if (buf[i] == '#')
			count_tetris++;
		else if (buf[i] == '\n')
			count_retour++;
		else if (buf[i] == '.')
			count++;
		else
			return (0);
		i++;
	}
	return ((count_tetris == 4 && (count_retour == 4 || count_retour == 5)
				&& count == 12) ? count_retour : 0);
}
