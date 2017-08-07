/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 01:48:06 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/06 23:19:17 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <time.h>

static int		check_same(int *tab, int size)
{
	int i;
	int j;

	i = 0;
	while (i < (size - 1))
	{
		j = i + 1;
		while (j < size)
		{
			if (tab[i] == tab[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void		one_pass(int *tab, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		tab[i] = (rand() + rand()) - INT_MAX;
		i++;
	}
}

static void		m_write(int *tab, int size)
{
	int i;

	i = 0;
	while (i < (size - 1))
		printf("%i ", tab[i++]);
	printf("%i\n", tab[i]);
}

int				main(int argc, char **argv)
{
	int *tab;
	int size;

	if (argc < 2)
	{
		fprintf(stderr, "You have to use argv[1]\n");
		return (-1);
	}
	if ((size = atoi(argv[1])) <= 0)
	{
		fprintf(stderr, "size must be at least 1\n");
		return (-1);
	}
	if (!(tab = (int *)malloc(size * sizeof(int))))
		return (-1);
	srand(time(NULL));
	one_pass(tab, size);
	while (!(check_same(tab, size)))
		one_pass(tab, size);
	m_write(tab, size);
	free(tab);
	return (0);
}
