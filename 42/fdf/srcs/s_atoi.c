/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nao_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:11:54 by saubenne          #+#    #+#             */
/*   Updated: 2017/05/02 14:12:42 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		get_error(int *error)
{
	*error = TRUE;
	return (0);
}

static int		atoi_hex(char *s, int *error)
{
	int nb;
	int i;
	int j;

	i = 0;
	nb = 0;
	if (ft_strncmp(s, "0x", 2) != 0)
		get_error(error);
	s += 2;
	while (s[i] != ' ' && s[i] != '\0')
	{
		j = 0;
		while (j != 16 && s[i] != HEX[j] && (s[i] - 32) != HEX[j])
			j++;
		if (j == 16)
			get_error(error);
		nb = nb * 16;
		nb += j;
		i++;
	}
	if (i < 1)
		get_error(error);
	return (nb);
}

static int		secure_mul(int a, int b, int *error)
{
	if (a > INT_MAX / b)
		*error = TRUE;
	if ((a < INT_MIN / b))
		*error = TRUE;
	if ((a == -1) && (b == INT_MIN))
		*error = TRUE;
	if ((b == -1) && (a == INT_MIN))
		*error = TRUE;
	return (a * b);
}

static int		secure_add(int a, int b, int *error)
{
	if ((a > 0) && (b > INT_MAX - a))
		*error = TRUE;
	if ((a < 0) && (b < INT_MIN - a))
		*error = TRUE;
	return (a + b);
}

void			ft_secure_atoi(const char *nptr, int *error, t_tile *tile)
{
	int result;
	int sign;

	*error = FALSE;
	result = 0;
	sign = FALSE;
	if (*nptr == '-')
	{
		sign = TRUE;
		nptr++;
	}
	if (!(*nptr >= '0' && *nptr <= '9'))
		*error = TRUE;
	else
		while (*nptr >= '0' && *nptr <= '9')
		{
			result = secure_mul(result, 10, error);
			result = secure_add(result, ((sign) ?
						-1 * (*nptr - '0') : (*nptr - '0')), error);
			nptr++;
		}
	tile->defined_color = (*nptr == ',') ? atoi_hex((char *)nptr + 1, error)
																	: 0xFFFFFF;
	tile->z = result;
	*error = (*nptr != ' ' && *nptr != ',' && *nptr != '\0') ? TRUE : *error;
}
