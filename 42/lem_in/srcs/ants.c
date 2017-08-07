/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:53:55 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/22 12:54:10 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		is_empty(t_pile *p, t_ant *f, int n)
{
	int i;

	i = 0;
	if (p->next == NULL)
		return (1);
	while (i < n)
	{
		if (f[i].loc == p)
			return (0);
		i++;
	}
	return (1);
}

static t_ant	*create_ants(t_pile *p, int n)
{
	t_ant	*f;
	int		i;

	if (!(f = (t_ant *)malloc(n * sizeof(t_ant))))
		return (NULL);
	i = 0;
	while (i < n)
	{
		f[i].nb = i + 1;
		f[i].loc = p;
		i++;
	}
	return (f);
}

void			go_moving(t_pile *p, int n)
{
	t_ant	*f;
	int		i;
	int		j;

	if (!(f = create_ants(p, n)))
		exit(EXIT_FAILURE);
	ft_printf("\n");
	while (f[n - 1].loc->next != NULL)
	{
		i = 0;
		j = 0;
		while (i < n)
		{
			if (f[i].loc->next != NULL && is_empty(f[i].loc->next, f, n))
			{
				ft_printf("%s", (j++ != 0) ? " " : "");
				f[i].loc = f[i].loc->next;
				ft_printf("L%i-%s", f[i].nb, ((t_room *)f[i].loc->pile)->name);
			}
			i++;
		}
		ft_printf("\n");
	}
	free(f);
}
