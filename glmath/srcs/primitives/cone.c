/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:12:35 by trossel           #+#    #+#             */
/*   Updated: 2022/06/09 15:06:19 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

#include <math.h>
#include <stdio.h>

#define TS_PHI M_PI_4 / 2
#define TS_RHO 0.5f

void	cone_normal_ray(t_ray *normal, t_cone *cone)
{
	t_ray	r;
	t_v3f	tmp;

	r = cylinder_world2cyl(normal, (t_cylinder *)cone);
	if (r.origin.y >= cone->height)
		normal->direction = cone->base[1];
	else if (r.origin.y <= 0)
		normal->direction = v3f_dot_scalar(&cone->base[1], -1.0f);
	else
	{
		tmp = v3f_cross_product(&(t_v3f){0.0f, 1.0f, 0.0f, 0.0f}, &r.origin);
		r.direction = v3f_cross_product(&tmp, &r.origin);
		v3f_normalize(&r.direction);
		*normal = cylinder_cyl2world(&r, (t_cylinder *)cone);
	}
}

float	cone_color_mask(const t_ray *normale, const t_cone *cone)
{
	t_ray	r;
	float	phi;
	float	rho;
	float	mask;

	r = cylinder_world2cyl(normale, (t_cylinder *)cone);
	rho = sqrt(r.origin.x * r.origin.x + r.origin.z * r.origin.z);
	phi = atan2f(r.origin.z, r.origin.x);
	mask = 1.0f;
	if (r.origin.y >= cone->height || r.origin.y <= 0)
	{
		if ((fabsf(fmodf(phi + 1000, 2 * TS_PHI)) < TS_PHI
		&& fabsf(fmodf(rho + 1000, 2 * TS_RHO)) > TS_RHO)
		|| (fabsf(fmodf(phi + 1000, 2 * TS_PHI)) > TS_PHI
		&& fmodf(rho, 2 * TS_RHO) < TS_RHO))
			mask = 0.5f;
	}
	else if ((fabsf(fmodf(phi + 1000, 2 * TS_PHI)) < TS_PHI
		&& fabsf(fmodf(r.origin.y + 1000, 2 * TS_RHO)) < TS_RHO)
		|| (fabsf(fmodf(phi + 1000, 2 * TS_PHI)) > TS_PHI
		&& fmodf(r.origin.y, 2 * TS_RHO) > TS_RHO))
		mask = 0.5f;
	return (mask);
}

t_color	cone_color_normal(const t_ray *normale, const t_cone *cone, float intensity)
{
	t_color	c;

	(void) normale;
	(void) cone;
	(void) intensity;
	c = color_create_int(0);
	return (c);
}

t_color	cone_color_texture(const t_ray *normale, const t_cone *cone, t_image *texture)
{
	t_color	c;

	(void) normale;
	(void) cone;
	(void) texture;
	c = color_create_int(0);
	return (c);
}

void	cone_print(const t_cone *cone)
{
	printf("\tCONE\n\torigin  = (%f, %f, %f)\n", cone->origin.x,
		cone->origin.y, cone->origin.z);
	printf("\tbase =      (%f, %f, %f)\n", cone->base[0].x, cone->base[1].x, cone->base[2].x);
	printf("\t            (%f, %f, %f)\n", cone->base[0].y, cone->base[1].y, cone->base[2].y);
	printf("\t            (%f, %f, %f)\n", cone->base[0].z, cone->base[1].z, cone->base[2].z);
	printf("\tinv. base = (%f, %f, %f)\n", cone->base_inv[0].x, cone->base_inv[1].x, cone->base_inv[2].x);
	printf("\t            (%f, %f, %f)\n", cone->base_inv[0].y, cone->base_inv[1].y, cone->base_inv[2].y);
	printf("\t            (%f, %f, %f)\n", cone->base_inv[0].z, cone->base_inv[1].z, cone->base_inv[2].z);
	printf("\tradius =  %f\n", cone->radius);
	printf("\theight =  %f\n", cone->height);
}
