/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 10:26:45 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/30 15:50:33 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

/* Used the formula described here:
 * https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
 * */

#define ANG (M_PI_4 / 2)

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

float	sphere_color_mask(const t_ray *normale, const t_sphere *sphere)
{
	float		theta;
	float		phi;

	theta = acosf(normale->direction.y);
	phi = atan2f(normale->direction.x, normale->direction.z);
	theta = fmod(theta, ANG);
	phi = fmod(phi, ANG);
	if (phi < 0)
		phi += ANG;
	if ((theta < ANG / 2 && phi < ANG / 2 )
		|| (theta >= ANG / 2 && phi >= ANG / 2 ))
		return (0.5f);
	(void)sphere;
	return (1.0f);
}

t_color	sphere_color_normal(const t_ray *normale, const t_sphere *sphere, float intensity)
{
	t_color	c;
	t_v3f	vect;

	vect = v3f_minus(&sphere->origin, &normale->origin);
	v3f_normalize(&vect);
	v3f_invers(&vect);
	cpy_vector_to_color(&c, &vect);
	c = color_mult_c(c, intensity);
	return (c);
}

void	sphere_print(const t_sphere *s)
{
	printf("\tSPHERE\n\torigin  = (%f, %f, %f)\n", s->origin.x,
		s->origin.y, s->origin.z);
	printf("\tradius  = %f\n", s->radius);
}
