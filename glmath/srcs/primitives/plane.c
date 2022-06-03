/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 21:35:39 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/03 09:22:56 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

int	plane_intersect(const t_ray *ray, const t_plane *plane, t_point3f *intersec)
{
	t_v3f	p0l0;
	float	t;
	float	denom;
	float	up;

	denom = v3f_scalar_product(&plane->normal, &ray->direction);
	p0l0 = v3f_minus(&plane->origin, &ray->origin);
	up = v3f_scalar_product(&p0l0, &plane->normal);
	if (fabsf(denom) < 1e-6 && fabsf(up) < 1e-6)
	{
		v3f_copy(intersec, &ray->origin);
		return (1);
	}
	else if (fabsf(denom) < 1e-6)
		return (0);
	else
	{
		t = up / denom;
		*intersec = ray_at(t, ray);
		return (t >= 0.0);
	}
	return (0);
}

void	plane_normal_ray(t_ray *normal_ray, t_plane *plane)
{
	v3f_copy(&normal_ray->direction, &plane->normal);
}
