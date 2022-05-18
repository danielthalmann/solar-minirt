/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 10:26:45 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/18 16:18:59 by trossel          ###   ########.fr       */
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
	printf("Intersection is at (%f, %f, %f)\n", intersection->x, intersection->y, intersection->z);
	return (1);
}


void	computeColorNormal(t_ray *ray, float dist, t_color *c, t_v3f *normal)
{
	(void)ray;
	(void)dist;
	(void)c;
	(void)normal;
	return ;
}
