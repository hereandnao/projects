/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 20:50:23 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/27 20:50:37 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "msa.h"

static int		usage(void)
{
	ft_eprintf("usage: ./msa [input_file].cor -o [output_file].s\n");
	return (-1);
}

static int		set_output_file(char **argv, int *i, int rab, char **file)
{
	char		*bout;

	if (rab < 2)
	{
		ft_eprintf("Not enough argument\n");
		return (-1);
	}
	if (*file)
	{
		ft_eprintf("Output_filename already defined !\n");
		return (-1);
	}
	(*i)++;
	bout = ft_strrchr(argv[*i], '.');
	if (bout == NULL || ft_strcmp(bout, ".s"))
	{
		ft_eprintf("Output file must end in .s !\n");
		return (-1);
	}
	*file = argv[*i];
	(*i)++;
	return (0);
}

static int		set_input_file(char **argv, int *i, char **file)
{
	char		*bout;

	if (*file)
	{
		ft_eprintf("input_filename already defined !\n");
		return (-1);
	}
	bout = ft_strrchr(argv[*i], '.');
	if (bout == NULL || ft_strcmp(bout, ".cor"))
	{
		ft_eprintf("Input file must end in .cor !\n");
		return (-1);
	}
	*file = argv[*i];
	(*i)++;
	return (0);
}

int				parse(int argc, char **argv, t_parse *files)
{
	int		i;
	int		ret;

	ft_bzero(files, sizeof(*files));
	ret = 0;
	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-o"))
			ret = set_output_file(argv, &i, argc - i, &files->output_file);
		else
			ret = set_input_file(argv, &i, &files->input_file);
		if (ret)
			return (usage());
	}
	if (!files->output_file || !files->input_file)
	{
		ft_eprintf("You must specify an input and an output file !\n");
		return (usage());
	}
	return (0);
}
