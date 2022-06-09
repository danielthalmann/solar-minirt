/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:11:15 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 11:15:52 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

#define TILE_SIZE 1.25f

float	plane_color_mask(const t_ray *normale, const t_plane *plane)
{
	int		v[3];
	t_v3f	io;

	v3f_copy(&io, &plane->origin);
	v3f_minus_equal(&io, &normale->origin);
	if (fabsf(io.x) < 1e-6)
		io.x = +0.0f;
	if (fabsf(io.y) < 1e-6)
		io.y = +0.0f;
	if (fabsf(io.z) < 1e-6)
		io.z = +0.0f;
	v[0] = ((abs((int)floorf(io.x / TILE_SIZE)) % 2) * 2) - 1;
	v[1] = ((abs((int)floorf(io.y / TILE_SIZE)) % 2) * 2) - 1;
	v[2] = ((abs((int)floorf(io.z / TILE_SIZE)) % 2) * 2) - 1;
	if (v[0] * v[1] * v[2] > 0)
		return (0.5f);
	else
		return (1.0f);
}

t_color	plane_color_normal(
	const t_ray *normale, const t_plane *plane, float intensity)
{
	t_color	c;

	(void) normale;
	(void) plane;
	(void) intensity;
	c = color_create_int(0);
	return (c);
}

t_color	plane_color_texture(
	const t_ray *normale, const t_plane *plane, t_image *texture)
{
	t_color	c;

	(void) normale;
	(void) plane;
	(void) texture;
	c = color_create_int(0);
	return (c);
}
