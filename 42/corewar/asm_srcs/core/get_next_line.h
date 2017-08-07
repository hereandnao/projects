/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 22:47:29 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/15 22:47:34 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

# define BUFF_SIZE 			4096
# define MAX_DESCRIPTORS   	65536

int					get_next_line(int const fd, char **line);

typedef struct		s_indexed_buffer
{
	int				fd;
	int				buff_size;
	char			buffer[BUFF_SIZE + 1];
}					t_indexed_buffer;

#endif
