/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:11:33 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/02 14:11:36 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		del(void *content, size_t i)
{
	(void)i;
	free(content);
}

static t_list	*extract_input(char *arg, int *size)
{
	t_list	*list;
	char	*get_line;
	int		fd;
	int		ret;

	*size = 0;
	list = NULL;
	if ((fd = open(arg, O_RDONLY)) < 0)
	{
		err_printf("Could not open %s : %s\n", arg, strerror(errno));
		return (NULL);
	}
	while ((ret = get_next_line(fd, &get_line)) > 0)
	{
		if (ft_push_front(&list, get_line, ret))
			return (NULL);
		(*size)++;
	}
	if (ret == -1)
		return (NULL);
	ft_listinvert(&list);
	return (list);
}

static t_tile	*create_tab(char *content, int *tabsize)
{
	t_tile		*new;
	int			err;
	int			j;

	j = 0;
	if ((*tabsize = count_nb(content)) == 0)
		return (NULL);
	if (!(new = malloc(*tabsize * sizeof(t_tile))))
		return (NULL);
	while (*content)
		if (*content != ' ')
		{
			ft_secure_atoi(content, &err, &new[j]);
			if (err)
			{
				ft_printf("ft_secure_atoi: Problem detected\n");
				return (NULL);
			}
			j++;
			while (*content && *content != ' ')
				content++;
		}
		else
			content++;
	return (new);
}

t_tile			**get_map(char *file, t_env *env)
{
	size_t	i;
	t_list	*input;
	t_list	*ptr;
	t_tile	**tile;
	int		old_size_x;

	if (!(input = extract_input(file, &env->size_y)) || env->size_y <= 0 ||
				(!(tile = (t_tile **)malloc(env->size_y * sizeof(t_tile *)))))
		return (NULL);
	i = 0;
	old_size_x = -1;
	ptr = input;
	while (input)
	{
		if (!(tile[i++] = create_tab(input->content, &env->size_x)))
			return (NULL);
		if (old_size_x < 0)
			old_size_x = env->size_x;
		else if (old_size_x != env->size_x)
			return (NULL);
		input = input->next;
	}
	ft_lstdel(&ptr, &del);
	return (tile);
}
