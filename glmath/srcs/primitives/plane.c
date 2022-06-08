/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 21:35:39 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/08 10:41:48 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

#define TILE_SIZE 1.25f

int	plane_intersect(const t_ray *ray, const t_plane *plane, t_point3f *intersec)
{
	t_v3f	p0l0;
	float	t;
	float	denom;
	float	up;

	denom = v3f_scalar_product(&plane->normal, &ray->direction);
	p0l0 = v3f_minus(&plane->origin, &ray->origin);
	up = v3f_scalar_product(&p0l0, &plane->normal);
	if (fabsf(denom) < 1e-6 && fabsf(up) < 1e-6)
	{
		v3f_copy(intersec, &ray->origin);
		return (1);
	}
	else if (fabsf(denom) < 1e-6)
		return (0);
	else
	{
		t = up / denom;
		*intersec = ray_at(0.99999 * t, ray);
		return (t >= 0.0);
	}
	return (0);
}

void	plane_normal_ray(t_ray *normal_ray, t_plane *plane)
{
	v3f_copy(&normal_ray->direction, &plane->normal);
}

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

t_color	plane_color_normal(const t_ray *normale, const t_plane *plane, float intensity)
{
	t_color	c;

	(void) normale;
	(void) plane;
	(void) intensity;
	c = color_create_int(0);
	return (c);
}

t_color	plane_color_texture(const t_ray *normale, const t_plane *plane, t_image *texture)
{
	t_color	c;

	(void) normale;
	(void) plane;
	(void) texture;
	c = color_create_int(0);
	return (c);
}

void	plane_print(const t_plane *p)
{
	printf("\tPLANE\n\torigin  = (%f, %f, %f)\n", p->origin.x,
		p->origin.y, p->origin.z);
	printf("\tnormale = (%f, %f, %f)\n", p->normal.x,
		p->normal.y, p->normal.z);
}
