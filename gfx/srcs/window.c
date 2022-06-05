/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 09:27:48 by trossel           #+#    #+#             */
/*   Updated: 2022/06/06 07:32:49 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "mlx.h"

#include <stdlib.h>

t_win	*win_init(t_gfx_ctx *ctx, int w, int h, char *title)
{
	t_win	*win;

	if (!ctx)
		return (NULL);
	win = malloc(sizeof(*win));
	if (!win)
		return (NULL);
	win->mlx_win = mlx_new_window(ctx->_ctx, w, h, title);
	if (!win->mlx_win)
	{
		free(win);
		return (NULL);
	}
	win->w = w;
	win->h = h;
	win->title = title;
	win->ctx = ctx;
	return (win);
}

void	win_free(t_win **win)
{
	mlx_destroy_window((*win)->ctx->_ctx, (*win)->mlx_win);
	free(*win);
	*win = NULL;
}

void	win_clear(t_win *win)
{
	mlx_clear_window(win->ctx->_ctx, win->mlx_win);
}
