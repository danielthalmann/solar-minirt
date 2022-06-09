/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 09:55:20 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/09 18:25:44 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

void	init_scene(t_scene *s)
{
	s->w = 0;
	s->h = 0;
	s->ratio = 0;
	s->cam.fov = -1.0f;
	s->cam.pos = (t_v3f){0.0f, 0.0f, 0.0f, 0.0f};
	s->cam.orien = (t_v3f){0.0f, 0.0f, 1.0f, 0.0f};
	s->cam.right = (t_v3f){1.0f, 0.0f, 0.0f, 0.0f};
	s->cam.up = (t_v3f){0.0f, 1.0f, 0.0f, 0.0f};
	s->ambient = (t_color){0.0f, 0.0f, 0.0f, 0.0f};
	s->ambient_intensity = -1.0f;
	s->lights = NULL;
	s->shapes = NULL;
	s->textures = NULL;
}

void	scene_around(t_scene *scene, void *data,
		void (*fn)(t_scene *, int, int, void *))
{
	t_point	pos;

	pos.y = 0;
	while (pos.y < scene->h)
	{
		pos.x = 0;
		while (pos.x < scene->w)
		{
			fn(scene, pos.x, pos.y, data);
			pos.x++;
		}
		pos.y++;
	}
}
