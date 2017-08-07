/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 12:25:29 by saubenne          #+#    #+#             */
/*   Updated: 2017/02/15 15:52:36 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	i_type(intmax_t *res, t_flags *args)
{
	if (args->if_lhjz == 0x00)
		*res = (int)*res;
	else if (args->if_lhjz & if_l)
		*res = (long int)*res;
	else if (args->if_lhjz & if_ll)
		*res = (long long int)*res;
	else if (args->if_lhjz & if_h)
		*res = (short int)*res;
	else if (args->if_lhjz & if_hh)
		*res = (char)*res;
	else if (args->if_lhjz & if_z)
		*res = (ssize_t) * res;
}

void	d_type(intmax_t *res, t_flags *args)
{
	if ((args->if_lhjz & if_l) || (args->c == 'D'))
		*res = (long int)*res;
	else if (args->if_lhjz == 0x00)
		*res = (int)*res;
	else if (args->if_lhjz & if_ll)
		*res = (long long int)*res;
	else if (args->if_lhjz & if_h)
		*res = (short int)*res;
	else if (args->if_lhjz & if_hh)
		*res = (char)*res;
	else if (args->if_lhjz & if_z)
		*res = (ssize_t) * res;
}

void	x_type(uintmax_t *res, t_flags *args)
{
	if (args->if_lhjz & if_l)
		*res = (unsigned long)*res;
	else if (args->if_lhjz == 0x00)
		*res = (unsigned int)*res;
	else if (args->if_lhjz & if_ll)
		*res = (unsigned long long)*res;
	else if (args->if_lhjz & if_h)
		*res = (unsigned short)*res;
	else if (args->if_lhjz & if_hh)
		*res = (unsigned char)*res;
	else if (args->if_lhjz & if_z)
		*res = (size_t)*res;
}

void	o_type(uintmax_t *res, t_flags *args)
{
	if ((args->if_lhjz & if_l) || (args->c == 'O'))
		*res = (unsigned long)*res;
	else if (args->if_lhjz == 0x00)
		*res = (unsigned int)*res;
	else if (args->if_lhjz & if_ll)
		*res = (unsigned long long)*res;
	else if (args->if_lhjz & if_h)
		*res = (unsigned short)*res;
	else if (args->if_lhjz & if_hh)
		*res = (unsigned char)*res;
	else if (args->if_lhjz & if_z)
		*res = (size_t)*res;
}

void	b_type(uintmax_t *res, t_flags *args)
{
	if (args->if_lhjz & if_l)
		*res = (unsigned long)*res;
	else if (args->if_lhjz == 0x00)
		*res = (unsigned int)*res;
	else if (args->if_lhjz & if_ll)
		*res = (unsigned long long)*res;
	else if (args->if_lhjz & if_h)
		*res = (unsigned short)*res;
	else if (args->if_lhjz & if_hh)
		*res = (unsigned char)*res;
	else if (args->if_lhjz & if_z)
		*res = (size_t)*res;
}
