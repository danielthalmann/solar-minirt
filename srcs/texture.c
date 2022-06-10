/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:46:43 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/09 13:33:28 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "main.h"
#include "mlx.h"

int	new_image(void *mlx_ptr, t_image *image, int w, int h)
{
	image->mlx_ptr = mlx_ptr;
	image->w = w;
	image->h = h;
	image->img_ptr = mlx_new_image(mlx_ptr, w, h);
	if (!image->img_ptr)
		return (1);
	image->c_ptr = (unsigned int *)mlx_get_data_addr
		(image->img_ptr, &(image->bpp), &(image->size_line), &image->endian);
	if (!image->c_ptr)
		return (1);
	image->bytes = image->bpp / 8;
	image->get_image_color = get_image_color;
	return (0);
}

/**
 * @brief Charge le sprite pour le joueur
 * 
 * @param f 
 */
void	load_texture_xpm(char *filename, void *mlx_ptr, t_image *image)
{
	int		*pwh[2];

	pwh[0] = (int *)&(image->w);
	pwh[1] = (int *)&(image->h);
	image->mlx_ptr = mlx_ptr;
	image->img_ptr = mlx_xpm_file_to_image(mlx_ptr, filename, pwh[0], pwh[1]);
	if (image->img_ptr)
	{
		image->c_ptr = (unsigned int *)mlx_get_data_addr
			(image->img_ptr, &(image->bpp),
				&(image->size_line), &(image->endian));
		image->bytes = image->bpp / 8;
	}
	else
		image->c_ptr = 0;
	image->get_image_color = get_image_color;
}

/**
 * @brief obtient la couleur de l'image au coordonnée x, y
 * 
 * @param i 
 * @param x 
 * @param y 
 * @return t_color 
 */
t_color	get_image_color(struct s_image *i, int x, int y)
{
	t_ui	color_int;

	x = x % i->w;
	y = y % i->h;
	if (!i || !i->c_ptr || x < 0 || x >= i->w || y < 0 || y >= i->h)
		return (color_create_int(0));
	color_int = i->c_ptr[((y) * i->size_line / i->bytes) + (x)];
	return (color_create_int(color_int));
}

void	set_image_color(t_image *i, int x, int y, t_color c)
{
	if (!i || !i->c_ptr || x < 0 || x >= i->w || y < 0 || y >= i->h)
		return ;
	i->c_ptr[(int)(x + (y * i->w))] = color_int(&c);
}
