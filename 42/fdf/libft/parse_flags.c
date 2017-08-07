/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 13:53:41 by saubenne          #+#    #+#             */
/*   Updated: 2017/02/18 15:25:41 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*get_letter(char *str)
{
	int		i;
	char	*sub;
	char	flags[16];

	ft_strcpy(flags, "sSpdDioOuUxXcCb%");
	i = 1;
	while (str[i] && (!(ft_strchr(flags, str[i]))))
	{
		i++;
	}
	sub = malloc((i + 2) * sizeof(char));
	ft_strncpy(sub, str, i + 1);
	sub[i + 1] = '\0';
	return (sub);
}

unsigned char		flag_analyzer(char *str)
{
	int				i;
	unsigned char	mask;

	mask = 0;
	i = 1;
	while (str[i])
	{
		if (str[i] == '#')
			mask = mask | hash;
		else if (str[i] == '0')
			mask = mask | zero;
		else if (str[i] == '-')
			mask = mask | minus;
		else if (str[i] == '+')
			mask = mask | plus;
		else if (str[i] == ' ')
			mask = mask | space;
		else
			break ;
		i++;
	}
	return (mask);
}

unsigned char		convert_detector(char *str, unsigned char flag)
{
	if (*str == '\0')
		return (flag);
	if (*str == 'l')
		flag = (flag & if_l) ? if_ll : if_l;
	else if (*str == 'h')
		flag = (flag & if_h) ? if_hh : if_h;
	else if (*str == 'j')
		flag = if_j;
	else if (*str == 'z')
		flag = if_z;
	return (convert_detector(str + 1, flag));
}
