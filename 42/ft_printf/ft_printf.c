/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:36:05 by saubenne          #+#    #+#             */
/*   Updated: 2017/03/06 14:03:20 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fn(g_fn[NUM_OF_FUNCTIONS]) =
{
	{'s', &nao_string},
	{'S', &nao_string},
	{'c', &nao_char},
	{'C', &nao_uchar},
	{'u', &nao_unsigned},
	{'U', &nao_unsigned},
	{'i', &nao_int},
	{'x', &nao_x},
	{'X', &nao_x},
	{'o', &nao_o},
	{'O', &nao_o},
	{'b', &nao_b},
	{'d', &nao_int},
	{'D', &nao_int},
	{'p', &nao_p},
	{'%', &nao_pourcent}
};

int		apply_fun(const char *s, int *ret, va_list *ap)
{
	char	*sub;
	int		i;
	int		size_sub;
	t_flags args;

	ft_bzero(&args, sizeof(t_flags));
	i = 0;
	sub = get_letter((char*)s);
	size_sub = (int)ft_strlen(sub) - 1;
	while (i < NUM_OF_FUNCTIONS && sub[size_sub] != g_fn[i].c)
		i++;
	if (i == NUM_OF_FUNCTIONS)
		*ret = -1;
	else
	{
		args = fill_struct(args, sub, ap);
		if ((i = g_fn[i].f(ap, &args)) == -1)
			*ret = -1;
		else
			*ret += i;
	}
	free(sub);
	return (size_sub + 1);
}

int		op_main(const char *s, va_list *ap, int ret)
{
	int		l;

	l = 0;
	while (s[l])
	{
		while (s[l] != '%' && s[l] != '\0')
			l++;
		ret += write(1, s, l);
		s = s + l;
		l = 0;
		if (s[l] == '%')
		{
			s += apply_fun(s, &ret, ap);
			if (ret == -1)
				return (-1);
		}
	}
	return (ret);
}

int		ft_printf(const char *s, ...)
{
	va_list	ap;
	int		ret;

	ret = 0;
	va_start(ap, s);
	ret = op_main(s, &ap, ret);
	va_end(ap);
	return (ret);
}
