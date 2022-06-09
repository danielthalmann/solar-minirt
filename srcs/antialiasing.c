/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:35:29 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 17:42:51 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "glmath.h"
#include "main.h"
#include "libft.h"
#include <unistd.h>

static t_color	get_average(t_image *img, int x, int y, int rank)
{
	t_color	color;
	t_color	tmp;
	int		delta[2];

	delta[0] = -rank;
	delta[1] = -rank;
	color.r = 0.0f;
	color.g = 0.0f;
	color.b = 0.0f;
	while (delta[1] <= rank)
	{
		tmp = get_image_color(img, x + delta[0], y + delta[1]);
		color.r += tmp.r;
		color.g += tmp.g;
		color.b += tmp.b;
		if (++(delta[0]) > rank)
		{
			delta[0] = -rank;
			delta[1]++;
		}
	}
	color.r /= pow(2 * rank + 1, 2);
	color.g /= pow(2 * rank + 1, 2);
	color.b /= pow(2 * rank + 1, 2);
	return (color);
}

/* 
 * @brief Apply a Box-filter to the image.
 *
 * @param img The image to apply the filter to
 * @param rank the size N of the matrix (2N + 1)x(2N + 1)
 * 			
 * 			rank = 0 => matrix is 1x1
 * 			rank = 1 => matrix is 3x3
 * 			rank = 2 => matrix is 5x5
 * */
void	mean_blur(t_image *img, int rank)
{
	int		x;
	int		y;
	t_color	c2;
	t_image	img2;

	if (rank < 0)
		rank = -rank;
	if (new_image(img->mlx_ptr, &img2, img->w, img->h))
		return ;
	x = 0;
	y = 0;
	while (y < img->h)
	{
		if (!x || x == img->w - 1 || !y || y == img->h -1)
			c2 = get_image_color(img, x, y);
		else
			c2 = get_average(img, x, y, rank);
		set_image_color(&img2, x, y, c2);
		if (++x == img->w)
		{
			x = 0;
			y++;
		}
	}
	ft_memcpy(img->c_ptr, img2.c_ptr, img->w * img->h * 4);
}
