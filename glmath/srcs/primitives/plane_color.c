/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:11:15 by trossel           #+#    #+#             */
/*   Updated: 2022/06/14 10:17:15 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

#define TILE_SIZE 2.00f

float	plane_color_mask(const t_ray *normale, const t_plane *plane)
{
	int		x;
	int		z;
	t_ray	r;

	r = ray_to_referential(&plane->ref, normale);
	x = floorf(r.origin.x / TILE_SIZE);
	z = floorf(r.origin.z / TILE_SIZE);
	if ((x + z) % 2)
		return (0.5f);
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
