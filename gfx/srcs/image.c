/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 09:28:57 by trossel           #+#    #+#             */
/*   Updated: 2022/06/05 10:33:24 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "mlx.h"

#include <stdlib.h>

t_img	*img_init(t_gfx_ctx *ctx, int w, int h)
{
	t_img	*img;

	if (!ctx)
		return (NULL);
	img = malloc(sizeof(*img));
	if (!img)
		return (NULL);
	img->mlx_img = mlx_new_image(ctx, w, h);
	if (!img->mlx_img)
	{
		free(img);
		return (NULL);
	}
	img->w = w;
	img->h = h;
	img->ctx = ctx;
	img->pixels = (unsigned int *)mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_size, &img->endian);
	return (img);
}

t_img	*img_from_xpm_file(t_gfx_ctx *ctx, char *filename)
{
	t_img	*img;

	if (!ctx)
		return (NULL);
	img = malloc(sizeof(*img));
	if (!img)
		return (NULL);
	img->mlx_img = mlx_xpm_file_to_image(ctx, filename, &img->w, &img->h);
	if (!img->mlx_img)
	{
		free(img);
		return (NULL);
	}
	img->ctx = ctx;
	img->pixels = (unsigned int *)mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_size, &img->endian);
	return (img);
}

int	img_get_pixel(t_img *img, int x, int y)
{
	return (img->pixels[(int)(x + (y * img->w))]);
}

void	img_set_pixel(t_img *img, int x, int y, int color)
{
	img->pixels[(int)(x + (y * img->w))] = color;
}

void	img_free(t_img **img)
{
	mlx_destroy_image((*img)->ctx, (*img)->mlx_img);
	free(*img);
	*img = NULL;
}

void	img_clear(t_img *img)
{
	(void)img;
	// ft_memset(img->pixels, 0, img->w * img->h * img->bpp / 8);
}

void	img_draw_to_win(t_img * img, t_win *win, int x, int y)
{
	mlx_put_image_to_window(win->ctx, win->mlx_win, img->mlx_img, x, y);
}
