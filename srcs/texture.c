/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 15:46:43 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/05 15:46:43 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
//	printf("\timage->w = %d\n", image->w);
//	printf("\timage->h = %d\n", image->h);	
//	printf("\timage->c_ptr = %p\n", image->c_ptr);
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
	
	if (!i->c_ptr)
		return (color_create_int(0));
	//x = x % i->w;
	//y = y % i->h;

	color_int = i->c_ptr[((y) * i->size_line / i->bytes) + (x)];
	return (color_create_int(color_int));
}
