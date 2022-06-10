/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:46:03 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 13:18:27 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"
#include "main.h"
#include "mlx.h"

static void	free_lights(t_light *l)
{
	t_light	*tmp;

	while (l)
	{
		tmp = l->next;
		free(l);
		l = tmp;
	}
}

static void	free_shapes(t_shape *s)
{
	t_shape	*tmp;

	while (s)
	{
		tmp = s->next;
		free(s);
		s = tmp;
	}
}

static void	free_textures(t_texture *tex)
{
	t_texture	*tmp;

	while (tex)
	{
		tmp = tex->next;
		//printf("free %s \n",tex->filename);
		//free(tex->filename);
		if (tex->image.img_ptr)
			mlx_destroy_image(tex->image.mlx_ptr, tex->image.img_ptr);
		free(tex);
		tex = tmp;
	}
}

void	free_app(t_app *app)
{
	free_shapes(app->scene.shapes);
	free_lights(app->scene.lights);
	free_textures(app->scene.textures);
	if (app->img.img_ptr)
		mlx_destroy_image(app->mlx, app->img.img_ptr);
	if (app->win_ptr)
		mlx_destroy_window(app->mlx, app->win_ptr);
}
