/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 19:59:19 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/27 19:59:21 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "msa.h"
#include "wof/wof.h"

static unsigned int		get_real_size(char prog_size[4])
{
	int				i;
	unsigned int	res;

	i = 0;
	res = 0;
	while (i < 4)
	{
		res <<= 8;
		res |= (prog_size[i] & 0xff);
		i++;
	}
	return (res);
}

static int				count_size_diff(t_env *e, unsigned int size)
{
	if (size <= 2192)
	{
		ft_eprintf("Error: filesize too short !\n");
		return (-1);
	}
	if (((e->size = (get_real_size(e->content->prog_size))) + 2192) != size)
	{
		ft_eprintf("Error: Mismatch between prog_size "
		"field and real file size.\n");
		return (-1);
	}
	return (0);
}

int						main(int argc, char **argv)
{
	t_env				env;
	t_parse				files;
	unsigned int		size;
	char				c;

	ft_bzero(&env, sizeof(env));
	if (parse(argc, argv, &files) ||
	!(env.content = read_file(files.input_file, &size, &c)))
		return (-1);
	if (count_size_diff(&env, size))
		return (-1);
	if ((check_file(env.content)))
		return (-1);
	if (init_wof(&env.wof, files.output_file))
		return (-1);
	if (fill_output(&env))
	{
		ft_eprintf("Error: Output file may be incomplete\n");
		return (-1);
	}
	if (close_wof(&env.wof))
		return (-1);
	free(env.content);
	ft_printf("{green}File %s saved !{eoc}\n", files.output_file);
	return (0);
}
