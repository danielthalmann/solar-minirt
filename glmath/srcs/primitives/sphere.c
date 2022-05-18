/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 10:26:45 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/18 17:19:22 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

int	sphere_intersect(t_ray *ray, void *s, t_v3f *intersection)
{
	t_v3f	oc;
	t_v3f	d;
	float	disc;
	t_sphere *sphere;

	sphere = (t_sphere *)s;
	oc = ray->origin;
	v3f_sub(&oc, &sphere->origin);
	disc = v3f_dot(&ray->direction, &oc);
	disc *= disc;
	disc -= (v3f_dot(&oc, &oc) - sphere->radius * sphere->radius);
	if (disc < 0.0f)
    	return (0);
	if (!intersection)
		return (1);
	v3f_copy(&d, &ray->direction);
	v3f_multi_v(&d, -(v3f_dot(&ray->direction, &oc) + disc));
	v3f_copy(intersection, &ray->origin);
	v3f_add(intersection, &d);
	// printf("Intersection is at (%f, %f, %f)\n", intersection->x, intersection->y, intersection->z);
	return (1);
}


void	sphere_normal_vector(t_v3f *normal, t_v3f *intersection, void *s)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)s;
	v3f_copy(normal, intersection);
	v3f_sub(normal, &sphere->origin);
	v3f_normalize(normal);
}
