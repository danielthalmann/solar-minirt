/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 21:35:39 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/25 10:12:59 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

int	plane_intersect(t_ray *ray, void *p, t_point3f *intersec)
{
	t_v3f	p0l0;

	float	t;
	t_plane	*plane;

	plane = (t_plane *)p;
	float denom = v3f_scalar_product(&plane->normal, &ray->direction); 
	if (denom > 1e-6) { 
		p0l0 = v3f_minus(&plane->origin, &ray->origin);
		t = v3f_scalar_product(&p0l0, &plane->normal) / denom;
		v3f_copy(intersec, &plane->origin);
		*intersec = ray_at(t, ray);
		return (t >= 0.0); 
	}
	return (0);
}
