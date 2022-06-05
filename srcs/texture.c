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
	t_color	c;

	c = color_create_int(0);
	if (x < 0 || y < 0 || x >= i->w || y >= i->h)
		return (c);
	(void) i;
	(void) x;
	(void) y;
	return (c);
}
