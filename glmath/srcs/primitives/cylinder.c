/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 10:26:45 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/07 15:54:22 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

#include <stdio.h>

void	cylinder_normal_ray(t_ray *normal, t_cylinder *cyl)
{
	t_v3f	tmp;
	// 1) Convert intersection point to cylinder coordinate system

	// 2)
	v3f_copy(&tmp, &normal->origin);
	tmp.y = 0;
	if (v3f_abs(&tmp) < cyl->radius)
	{
		v3f_copy(&normal->direction, &cyl->base[2]);
		if (fabsf(normal->origin.y) < 1e-4)
			v3f_dot_equal_scalar(&normal->direction, -1.0f);
		return ;
	}
	v3f_copy(&normal->direction, &normal->origin);
	v3f_minus_equal(&normal->direction, &cyl->origin);
	v3f_normalize(&normal->direction);

	// 3) Convert back to world coordinates
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
	printf("\tnormale = (%f, %f, %f)\n", cyl->base[2].x,
		cyl->base[2].y, cyl->base[2].z);
	printf("\tradius =  %f\n", cyl->radius);
	printf("\theight =  %f\n", cyl->height);
}
