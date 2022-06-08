/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 10:26:45 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/08 10:48:53 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

#include <stdio.h>

t_ray	cylinder_world2cyl(const t_ray *world_ray, const t_cylinder *c)
{
	t_ray	cyl_ray;

	v3f_copy(&cyl_ray.origin, &world_ray->origin);
	v3f_minus_equal(&cyl_ray.origin, &c->origin);
	cyl_ray.origin = matrix_dot_v3f(c->base_inv, &cyl_ray.origin);
	cyl_ray.direction = matrix_dot_v3f(c->base_inv, &world_ray->direction);
	return (cyl_ray);
}

t_ray	cylinder_cyl2world(const t_ray *cyl_ray, const t_cylinder *c)
{
	t_ray	world_ray;

	v3f_copy(&world_ray.origin, &cyl_ray->origin);
	world_ray.origin = matrix_dot_v3f(c->base, &world_ray.origin);
	v3f_plus_equal(&world_ray.origin, &c->origin);
	world_ray.direction = matrix_dot_v3f(c->base, &cyl_ray->direction);
	return (world_ray);
}

void	cylinder_normal_ray(t_ray *normal, t_cylinder *cyl)
{
	t_ray	r;

	r = cylinder_world2cyl(normal, cyl);
	if (r.origin.y >= cyl->height)
		normal->direction = cyl->base[1];
	else if (r.origin.y <= 0)
	{
		normal->direction = v3f_dot_scalar(&cyl->base[1], -1.0f);
		// printf("-N = (%f, %f, %f)\n", r.direction.x, r.direction.y, r.direction.z);
	}
	else
	{
		r.direction = r.origin;
		r.direction.y = 0;
		v3f_normalize(&r.direction);
		*normal = cylinder_cyl2world(&r, cyl);
	}
}

float	cylinder_color_mask(const t_ray *normale, const t_cylinder *cyl)
{
	(void)normale;
	(void)cyl;
	return (1.0f);
}

t_color	cylinder_color_normal(const t_ray *normale, const t_cylinder *cyl, float intensity)
{
	t_color	c;

	(void) normale;
	(void) cyl;
	(void) intensity;
	c = color_create_int(0);
	return (c);
}

t_color	cylinder_color_texture(const t_ray *normale, const t_cylinder *cyl, t_image *texture)
{
	t_color	c;

	(void) normale;
	(void) cyl;
	(void) texture;
	c = color_create_int(0);
	return (c);
}

void	cylinder_print(const t_cylinder *cyl)
{
	printf("\tCYLINDER\n\torigin  = (%f, %f, %f)\n", cyl->origin.x,
		cyl->origin.y, cyl->origin.z);
	printf("\tbase =      (%f, %f, %f)\n", cyl->base[0].x, cyl->base[1].x, cyl->base[2].x);
	printf("\t            (%f, %f, %f)\n", cyl->base[0].y, cyl->base[1].y, cyl->base[2].y);
	printf("\t            (%f, %f, %f)\n", cyl->base[0].z, cyl->base[1].z, cyl->base[2].z);
	printf("\tinv. base = (%f, %f, %f)\n", cyl->base_inv[0].x, cyl->base_inv[1].x, cyl->base_inv[2].x);
	printf("\t            (%f, %f, %f)\n", cyl->base_inv[0].y, cyl->base_inv[1].y, cyl->base_inv[2].y);
	printf("\t            (%f, %f, %f)\n", cyl->base_inv[0].z, cyl->base_inv[1].z, cyl->base_inv[2].z);
	printf("\tradius =  %f\n", cyl->radius);
	printf("\theight =  %f\n", cyl->height);
}
