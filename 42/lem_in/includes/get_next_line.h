/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 01:44:48 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/11 01:45:48 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

# define BUFF_SIZE 			256
# define MAX_DESCRIPTORS   	65536

typedef struct		s_buffer
{
	int				fd;
	int				buff_size;
	char			buffer[BUFF_SIZE + 1];
}					t_buffer;

typedef struct		s_swiss
{
	int				a;
	int				b;
}					t_swiss;

int					get_next_line (const int fd, char **line);
int					swiss_line (const int fd, char **line,
												t_swiss p, char *needdle);
#endif
