/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 18:22:30 by bmickael          #+#    #+#             */
/*   Updated: 2017/04/10 23:23:27 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_printf.h"

static int			compare(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s2[i] != 0x00 && s1[i] != 0x00 && (s1[i] == s2[i]))
		i++;
	if (s1[i] == 0x00)
		return (i);
	return (0);
}

static const char	*g_modifier_list[MODIFIER_QUANTITY][2] = {
	{ "{eoc}", "\x1B[0m" },
	{ "{red}", "\x1B[31m" },
	{ "{green}", "\x1B[32m" },
	{ "{yellow}", "\x1B[33m" },
	{ "{blue}", "\x1B[34m" },
	{ "{magenta}", "\x1B[35m" },
	{ "{cyan}", "\x1B[36m" },
	{ "{white}", "\x1B[37m" },
	{ "{red_bg}", "\e[41m" },
	{ "{green_bg}", "\e[42m" },
	{ "{blue_bg}", "\e[44m" },
	{ "{magenta_bg}", "\e[45m" },
	{ "{light_blue}", "\e[94m" },
	{ "{red_ul}", "\e[4;31m" },
	{ "{green_ul}", "\e[4;32m" },
	{ "{blue_ul}", "\e[4;34m" },
	{ "{magenta_ul}", "\e[4;35m" },
	{ "{cyan_ul}", "\e[4;36m" },
	{ "{yellow_ul}", "\e[4;33m" }
};

void				assign_modifier(t_status *op)
{
	int l;
	int j;

	l = 0;
	while (l < MODIFIER_QUANTITY)
	{
		if (compare(g_modifier_list[l][0], op->s))
		{
			op->s += ft_strlen(g_modifier_list[l][0]);
			j = ft_strlen(g_modifier_list[l][1]);
			if (!assign_segment(j, op))
				return ;
			ft_memcpy(op->ptr, g_modifier_list[l][1], j);
			return ;
		}
		l++;
	}
	op->s += 1;
	if (!assign_segment(1, op))
		return ;
	*(op->ptr) = '{';
}
