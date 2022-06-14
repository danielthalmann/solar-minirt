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

/**
 * @brief Charge en mémoire les textures et assigne les textures sur les objets
 * 
 * @param app 
 */
void	init_texture(t_app *app)
{
	t_texture	*tex;
	t_shape		*shape;

	tex = app->scene.textures;
	while (tex)
	{
		load_texture_xpm(tex->filename, app->mlx, &tex->image);
		tex = tex->next;
	}
	shape = app->scene.shapes;
	while (shape)
	{
		shape->texture[0] = get_texture_idx(app->scene.textures,
				shape->tex_id[0]);
		shape->texture[1] = get_texture_idx(app->scene.textures,
				shape->tex_id[1]);
		shape->normal_map = get_texture_idx(app->scene.textures, shape->nm_id);
		shape = shape->next;
	}
}

/**
 * @brief retourne la texture en fonction de l'index de celle-ci
 * 
 * @param textures 
 * @param index 
 * @return t_texture* 
 */
t_texture	*get_texture_idx(t_texture *textures, int index)
{
	t_texture	*tex;
	int			i;

	if (index < 0)
		return (NULL);
	i = 0;
	tex = textures;
	while (tex && i < index)
	{
		tex = tex->next;
		i++;
	}
	if (i != index)
		return (NULL);
	return (tex);
}
