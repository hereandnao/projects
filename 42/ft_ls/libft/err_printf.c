/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 17:36:05 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/18 17:44:16 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_fn(g_fn[NUM_OF_FUNCTIONS]) =
{
	{'s', &err_string},
	{'S', &err_string},
	{'c', &err_char},
	{'C', &err_uchar},
	{'u', &err_unsigned},
	{'U', &err_unsigned},
	{'i', &err_int},
	{'x', &err_x},
	{'X', &err_x},
	{'o', &err_o},
	{'O', &err_o},
	{'b', &err_b},
	{'d', &err_int},
	{'D', &err_int},
	{'p', &err_p},
	{'%', &err_pourcent}
};

static int		apply_fun(const char *s, int *ret, va_list *ap)
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

static int		op_main(const char *s, va_list *ap, int ret)
{
	int		l;

	l = 0;
	while (s[l])
	{
		while (s[l] != '%' && s[l] != '\0')
			l++;
		ret += write(2, s, l);
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

int				err_printf(const char *s, ...)
{
	va_list	ap;
	int		ret;

	ret = 0;
	va_start(ap, s);
	ret = op_main(s, &ap, ret);
	va_end(ap);
	return (ret);
}
