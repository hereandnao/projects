/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:24:12 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/20 18:34:40 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>
#include "ft_ls.h"
#include <string.h>

int		main(int argc, char **argv)
{
	t_lst_duo	t;
	t_opts		flags;

	flags = 0;
	ft_bzero(&t, sizeof(t_lst_duo));
	parse(argc, argv, &t, &flags);
	return (0);
}
