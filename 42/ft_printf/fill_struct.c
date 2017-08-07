/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 13:19:23 by saubenne          #+#    #+#             */
/*   Updated: 2017/02/15 13:20:14 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags	fill_struct(t_flags args, char *sub, va_list *ap)
{
	args.mask = flag_analyzer(sub);
	args.c = sub[ft_strlen(sub) - 1];
	args.width = get_width(sub, ap, &args);
	args.preci = get_preci(sub, ap);
	args.if_lhjz = convert_detector(sub, args.if_lhjz);
	return (args);
}
