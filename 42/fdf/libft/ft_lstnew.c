/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saubenne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:47:01 by saubenne          #+#    #+#             */
/*   Updated: 2017/04/19 22:49:14 by saubenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		*s_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*src1;
	char		*dest1;

	src1 = (char *)src;
	dest1 = (char *)dest;
	i = 0;
	while (i < n)
	{
		dest1[i] = src1[i];
		i++;
	}
	return (dest);
}

t_list			*ft_lstnew(void const *content, size_t content_size)
{
	t_list *output;

	if ((output = (t_list *)malloc(sizeof(t_list))))
	{
		if (!content)
		{
			output->content = NULL;
			output->content_size = 0;
			return (output);
		}
		else if ((output->content = (char *)
			malloc(content_size * sizeof(char))))
		{
			s_memcpy(output->content, content, content_size);
			output->content_size = content_size;
			output->next = NULL;
			return (output);
		}
		free(output);
	}
	return (NULL);
}
