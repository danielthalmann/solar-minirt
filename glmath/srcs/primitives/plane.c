/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 21:35:39 by dthalman          #+#    #+#             */
/*   Updated: 2022/05/20 21:35:39 by dthalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

int	plane_intersect(t_ray *ray, void *p, t_point3f *intersec)
{
	t_v3f		oc;
	float		t;
	t_plane	*plane;

	plane = (t_plane *)p;
	float denom = v3f_scalar_product(plane->normal, ray->direction); 
	if (denom > 1e-6) { 
		t_v3f p0l0 = v3f_minus(plane->origin, ray->origin);
		t_v3f dot = v3f_division(v3f_dot_scalar(p0l0, plane->normal), denom);
		return (t >= 0); 
	}
	return (0);
}

