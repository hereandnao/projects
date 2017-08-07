/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wof.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 19:59:39 by bmickael          #+#    #+#             */
/*   Updated: 2017/07/27 19:59:41 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOF_H
# define WOF_H

struct s_wof;

int		init_wof(struct s_wof **ctx, char *filename);
int		wof(struct s_wof *ctx, char *str, ...);
int		put(struct s_wof *ctx, char *str, ...);
int		close_wof(struct s_wof **ctx);

#endif
