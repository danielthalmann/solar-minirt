/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 21:35:39 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/14 07:46:52 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

int	plane_intersect(const t_ray *ray, const t_plane *plane, t_point3f *interse)
{
	t_v3f	p0l0;
	float	t;
	float	denom;
	float	up;

	denom = v3f_scalar_product(&plane->ref.b[1], &ray->direction);
	p0l0 = v3f_minus(&plane->ref.p, &ray->origin);
	up = v3f_scalar_product(&p0l0, &plane->ref.b[1]);
	if (fabsf(denom) < 1e-6 && fabsf(up) < 1e-6)
	{
		v3f_copy(interse, &ray->origin);
		return (1);
	}
	else if (fabsf(denom) < 1e-6)
		return (0);
	else
	{
		t = up / denom;
		*interse = ray_at(0.99999 * t, ray);
		return (t >= 0.0);
	}
	return (0);
}

void	plane_normal_ray(t_ray *normal_ray, t_plane *plane)
{
	v3f_copy(&normal_ray->direction, &plane->ref.b[1]);
}

void	plane_print(const t_plane *p)
{
	printf("\tPLANE\n\torigin  = (%f, %f, %f)\n", p->ref.p.x,
		p->ref.p.y, p->ref.p.z);
	printf("\tref.b[1]e = (%f, %f, %f)\n", p->ref.b[1].x,
		p->ref.b[1].y, p->ref.b[1].z);
}
