/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 10:26:45 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/25 14:06:43 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

/* Used the formula described here:
 * https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
 * */
int	sphere_intersect(t_ray *ray, void *s, t_point3f *intersec)
{
	t_v3f		oc;
	float		disc;
	t_sphere	*sphere;

	sphere = (t_sphere *)s;
	oc = v3f_minus(&ray->origin, &sphere->origin);

	disc = v3f_scalar_product(&ray->direction, &oc);
	disc *= disc;
	disc -= (v3f_scalar_product(&oc, &oc) - sphere->radius * sphere->radius);
	if (disc < 0.0f)
		return (0);
	if (!intersec)
		return (1);
	disc = sqrtf(disc);
	intersec = ray_at(-(v3f_scalar_product(&ray->direction, &oc) + disc), ray);
	return (1);
}

void	sphere_normal_vector(t_ray *normal, void *shape, t_point3f *intersec)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)shape;
	v3f_copy(&normal->origin, intersec);
	v3f_copy(&normal->direction, intersec);
	v3f_minus_equal(&normal->direction, &sphere->origin);
	v3f_normalize(&normal->direction);
}

void	sphere_print(t_sphere *s)
{
	printf("\tSPHERE\n\torigin  = (%f, %f, %f)\n", s->origin.x,
		s->origin.y, s->origin.z);
	printf("\tradius  = %f\n", s->radius);
}
