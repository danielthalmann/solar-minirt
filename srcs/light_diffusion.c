/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_diffusion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:15:29 by trossel           #+#    #+#             */
/*   Updated: 2022/06/08 14:13:00 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

t_color	compute_diffuse_color(t_ray *normal_ray, const t_shape *shape,
		const t_light *light, const t_color color)
{
	t_v3f	il;
	float	dot;
	t_color	c;

	c = color_create_int(0);
	v3f_copy(&il, &light->origin);
	v3f_minus_equal(&il, &normal_ray->origin);
	v3f_normalize(&il);
	dot = v3f_scalar_product(&normal_ray->direction, &il);
	dot *= light->intensity;
	if (dot < 0.0f)
	{
		if (shape->type == PLANE)
			dot = -dot;
		else
			return (c);
	}
	c = color_mult_c(color, dot);
	c = color_mult(c, light->color);
	return (c);
}

t_color	compute_normal_mapping(
		t_ray *normal_ray, const t_shape *shape, const t_light *light,
		t_image *textures)
{
	t_v3f	up;
	t_v3f	map_normal;
	t_v3f	m[3];
	t_ray	normal;
	t_color	c;

	c = shape->color_texture(normal_ray, &shape->shape, textures);
	v3f_set(&map_normal, c.r, c.g, c.b);
	v3f_copy(&m[2], &normal_ray->direction);
	v3f_normalize(&m[2]);
	if (fabsf(m[2].z) < 1e-6 && fabsf(m[2].x) < 1e-6)
		v3f_set(&up, 0.0, 1.0, 0.0);
	else
		v3f_set(&up, 1.0, 0.0, 0.0);
	m[0] = v3f_cross_product(&m[2], &up);
	v3f_normalize(&m[0]);
	m[1] = v3f_cross_product(&m[2], &m[0]);
	v3f_normalize(&m[1]);
	map_normal = v3f_dot_scalar(&map_normal, 2);
	map_normal = v3f_minus_val(&map_normal, 1);
	map_normal = matrix_dot_v3f(m, &map_normal);
	v3f_normalize(&map_normal);
	normal.origin = normal_ray->origin;
	normal.direction = map_normal;
	return (compute_diffuse_color(&normal, shape, light, shape->color));
}
