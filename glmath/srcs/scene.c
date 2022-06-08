/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 09:55:20 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/08 17:12:21 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

void	init_scene(t_scene *s)
{
	s->cam.fov = -1.0f;
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
