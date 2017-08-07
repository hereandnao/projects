/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 23:25:55 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/15 23:25:58 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				secure_atoi(const char *nptr, int *error)
{
	int			res;
	int			sign;

	*error = FALSE;
	res = 0;
	sign = FALSE;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = TRUE;
		nptr++;
	}
	if (!(*nptr >= '0' && *nptr <= '9'))
		*error = TRUE;
	else
		while (*nptr >= '0' && *nptr <= '9')
		{
			res *= 10;
			res = (sign) ? res - (*nptr - '0') : res + (*nptr - '0');
			nptr++;
		}
	if (*nptr != '\0')
		*error = TRUE;
	return (res);
}
