/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 10:26:45 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/30 08:47:52 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

/* Used the formula described here:
 * https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
 * */
int	sphere_intersect(const t_ray *ray, const t_sphere *sph, t_point3f *inter)
{
	t_v3f		oc;
	float		disc;
	float		t;

	oc = v3f_minus(&ray->origin, &sph->origin);
	disc = v3f_scalar_product(&ray->direction, &oc);
	disc *= disc;
	disc -= (v3f_scalar_product(&oc, &oc) - sph->radius * sph->radius);
	if (disc < 0.0f)
		return (0);
	if (!inter)
		return (1);
	disc = sqrtf(disc);
	t = -(v3f_scalar_product(&ray->direction, &oc) + disc);
	if (t < 0)
		t = -(v3f_scalar_product(&ray->direction, &oc) - disc);
	if (t < 0)
		return (0);
	*inter = ray_at(t, ray);
	return (1);
}

void	sphere_normal_ray(t_ray *normal, t_sphere *sphere)
{
	v3f_copy(&normal->direction, &normal->origin);
	v3f_minus_equal(&normal->direction, &sphere->origin);
	v3f_normalize(&normal->direction);
}

void	sphere_print(t_sphere *s)
{
	printf("\tSPHERE\n\torigin  = (%f, %f, %f)\n", s->origin.x,
		s->origin.y, s->origin.z);
	printf("\tradius  = %f\n", s->radius);
}
