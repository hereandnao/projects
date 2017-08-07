/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 19:59:51 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/27 19:59:53 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include "libft.h"
#include "int_wof.h"

int		init_wof(struct s_wof **ctx, char *filename)
{
	if (!(*ctx = (t_wof *)ft_memalloc(sizeof(t_wof))))
		return (-1);
	(*ctx)->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*ctx)->fd < 0)
	{
		ft_eprintf("init_wof: %s\n", strerror(errno));
		return (-1);
	}
	return (0);
}

int		wof(struct s_wof *ctx, char *str, ...)
{
	int		ret;
	va_list	args;

	va_start(args, str);
	ret = ft_h_printf(ctx->fd, str, args);
	va_end(args);
	if (ret < 0)
	{
		ft_eprintf("wof: %s\n", strerror(errno));
		return (-1);
	}
	ret = write(ctx->fd, "\n", 1);
	if (ret < 0)
	{
		ft_eprintf("wof: %s\n", strerror(errno));
		return (-1);
	}
	return (0);
}

int		put(struct s_wof *ctx, char *str, ...)
{
	int		ret;
	va_list	args;

	va_start(args, str);
	ret = ft_h_printf(ctx->fd, str, args);
	va_end(args);
	if (ret < 0)
	{
		ft_eprintf("wof: %s\n", strerror(errno));
		return (-1);
	}
	return (0);
}

int		close_wof(struct s_wof **ctx)
{
	int ret;

	ret = 0;
	if (*ctx)
		ret = close((*ctx)->fd);
	if (ret < 0)
	{
		ft_eprintf("close_wof: %s\n", strerror(errno));
		return (-1);
	}
	if (*ctx)
		free(*ctx);
	*ctx = NULL;
	return (0);
}
