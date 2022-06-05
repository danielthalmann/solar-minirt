/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 22:02:59 by trossel           #+#    #+#             */
/*   Updated: 2022/06/05 23:08:59 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "mlx.h"

#include <stddef.h>

void	img_clear(t_img *img)
{
	unsigned char	*p;
	size_t			len;

	p = (unsigned char *)img->pixels;
	len = img->w * img->h * img->bpp / 8;
	while (len--)
		*(p++) = 0;
}

void	img_draw_to_win(t_img *img, t_win *win, int x, int y)
{
	mlx_put_image_to_window(img->ctx->mlx, win, img, x, y);
}
