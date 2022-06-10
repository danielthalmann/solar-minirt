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
 * @brief Charge en mémoire les textures
 * 
 * @param app 
 */
void	init_texture(t_app *app)
{
	t_texture	*tex;

	tex = app->scene.textures;
	while (tex)
	{
		load_texture_xpm(tex->filename, app->mlx, &tex->image);
		tex = tex->next;
	}
}

t_texture	*get_texture_idx(t_texture *textures, int index)
{
	t_texture	*tex;
	int			i;

	if (index < 0)
		return (NULL);
	i = 0;
	tex = textures;
	while (tex && i < index)
		tex = tex->next;
	return (tex);
}