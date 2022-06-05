/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 09:28:57 by trossel           #+#    #+#             */
/*   Updated: 2022/06/06 07:32:45 by trossel          ###   ########.fr       */
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
	img->lib_img = mlx_new_image(ctx->_ctx, w, h);
	if (!img->lib_img)
	{
		free(img);
		return (NULL);
	}
	img->w = w;
	img->h = h;
	img->ctx = ctx;
	img->pixels = (unsigned int *)mlx_get_data_addr(img->lib_img, &img->bpp,
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
	img->lib_img = mlx_xpm_file_to_image(ctx->_ctx, filename, &img->w, &img->h);
	if (!img->lib_img)
	{
		free(img);
		return (NULL);
	}
	img->ctx = ctx;
	img->pixels = (unsigned int *)mlx_get_data_addr(img->lib_img, &img->bpp,
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
	mlx_destroy_image((*img)->ctx->_ctx, (*img)->lib_img);
	free(*img);
	*img = NULL;
}
