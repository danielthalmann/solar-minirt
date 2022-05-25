/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 21:35:39 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/25 17:05:51 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

int	plane_intersect(t_ray *ray, t_plane *plane, t_point3f *intersec)
{
	t_v3f	p0l0;
	float	t;

	float denom = v3f_scalar_product(&plane->normal, &ray->direction);
	if (denom > 1e-6 || denom < -1e-6) {
		p0l0 = v3f_minus(&plane->origin, &ray->origin);
		// p0l0 = v3f_minus(&ray->origin, &plane->origin);
		t = v3f_scalar_product(&p0l0, &plane->normal) / denom;
		*intersec = ray_at(t, ray);
		return (t >= 0.0);
	}
	return (0);
}

#include <stdio.h>
void	plane_normal_ray(t_ray *normal_ray, t_plane *plane)
{
	// printf("haha");
	v3f_copy(&normal_ray->direction, &plane->normal);
}
