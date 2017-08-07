/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 23:43:42 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/15 23:43:44 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"

static t_list	*apply_label_modifications(t_map *map)
{
	t_list		*ptr_jmp;
	t_list		*ptr_first;
	t_label		*lab_jmp;
	t_label		*lab_first;

	ptr_jmp = map->label_map;
	while (ptr_jmp)
	{
		while (ptr_jmp && (lab_jmp = ptr_jmp->content)->jmp_value == 0xFFFF)
			ptr_jmp = ptr_jmp->next;
		ptr_first = map->label_map;
		while (ptr_jmp && ptr_first && (lab_first = ptr_first->content))
			if (!ft_strcmp(lab_first->name, lab_jmp->name) &&
			lab_first->jmp_value == 0xFFFF)
			{
				write_direct_value(map->buff + (sizeof(t_header)) +
				lab_jmp->origin, lab_first->origin - lab_jmp->jmp_value,
															lab_jmp->size);
				break ;
			}
			else if (!(ptr_first = ptr_first->next))
				return (ptr_jmp);
		ptr_jmp = (ptr_jmp) ? ptr_jmp->next : NULL;
	}
	return (NULL);
}

/*
** Seule la bad allocation est à considérer comme une erreure dans la
** fonction ci-dessous:
*/

int				test_label_at_first(char *line, t_map *map)
{
	int			i;
	t_list		*t;
	t_label		*lab;

	i = -1;
	while (line[++i] && is_label_char(line[i]))
		;
	if (line[i] != ':' || (i == 0))
		return (0);
	t = NULL;
	while ((t = (!t) ? map->label_map : t->next) &&
		(lab = t->content))
		if (i == (int)ft_strlen(lab->name) && !ft_strncmp(line, lab->name, i) &&
			lab->jmp_value == 0xFFFF)
			return (i + 1);
	if (!(lab = (t_label *)ft_memalloc(sizeof(t_label))))
		exit(EXIT_FAILURE);
	lab->origin = map->ptr - (map->buff + (sizeof(t_header)));
	lab->jmp_value = 0xFFFF;
	if (!(lab->name = (char *)ft_memalloc((i + 1) * sizeof(char))))
		exit(EXIT_FAILURE);
	ft_strncpy(lab->name, line, i);
	secure_lst(&map->label_map, ft_lstnew(lab, sizeof(t_label)));
	free(lab);
	return (i + 1);
}

char			*assign_label_jump(char *s, t_map *map, int size)
{
	int			i;
	t_label		*label;

	i = 0;
	while (s[i] && is_label_char(s[i]))
		i++;
	if (s[i] != '\0' || (i == 0))
		return (ERR_LABEL_JUMP);
	if (!(label = (t_label *)ft_memalloc(sizeof(t_label))))
		exit(EXIT_FAILURE);
	label->jmp_value = map->origin_op - (map->buff + (sizeof(t_header)));
	label->origin = map->ptr - (map->buff + (sizeof(t_header)));
	if (!(label->name = (char *)ft_memalloc((i + 1) * sizeof(char))))
		exit(EXIT_FAILURE);
	label->size = size;
	ft_strncpy(label->name, s, i);
	secure_lst(&map->label_map, ft_lstnew(label, sizeof(t_label)));
	free(label);
	return (NULL);
}

int				manage_label_modifications(t_map *map)
{
	t_list		*ptr;
	t_label		*label;

	if ((ptr = apply_label_modifications(map)))
	{
		label = ptr->content;
		ft_eprintf(ERR_LABEL_ASSIGN, label->name);
		ft_lstdel(&map->label_map, &del_label);
		return (0);
	}
	ft_lstdel(&map->label_map, &del_label);
	return (1);
}

void			del_label(void *container, size_t size)
{
	t_label *tmp;

	(void)size;
	tmp = container;
	free(tmp->name);
	free(tmp);
}
