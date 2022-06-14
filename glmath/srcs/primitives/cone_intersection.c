/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 10:26:45 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/14 07:36:59 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

#include <stdio.h>

// static int	check_ends(t_ray *r, const t_cone *cyl, t_point3f *inter)
// {
// 	float	t_ends[2];
//
// 	if (fabsf(r->direction.y) < 1e-6)
// 		return (0);
// 	t_ends[0] = (0.0f - r->origin.y) / r->direction.y;
// 	t_ends[1] = (cyl->height - r->origin.y) / r->direction.y;
// 	return (0);
// }

// t_sides are the coefficients for the ray to reach the walls of the cone.
static float	check_height(t_ray *r, const t_cone *c, float t_sides[2])
{
	t_v3f	inters[3];
	float	t_end;
	float	real_t;
	float	rho;

	real_t = -1.0f;
	t_end = -2.0f;
	if (fabsf(r->direction.y) > 1e-6)
		t_end = (c->height - r->origin.y) / r->direction.y;
	inters[0] = ray_at(t_sides[0], r);
	inters[1] = ray_at(t_sides[1], r);
	inters[2] = ray_at(t_end, r);
	rho = sqrtf(inters[2].x * inters[2].x + inters[2].z * inters[2].z);
	if (t_sides[0] >= 0 && inters[0].y >= 0 && inters[0].y <= c->height)
		real_t = t_sides[0];
	if (t_end >= 0 && rho < c->radius && (real_t < 0.0f || t_end < real_t))
		real_t = t_end;
	if (t_sides[1] >= 0 && (t_sides[1] < real_t || real_t < 0.0f)
		&& inters[1].y >= 0 && inters[1].y <= c->height)
		real_t = t_sides[1];
	return (real_t);
}

/* Used the formula described here:
 * https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html
 */
int	cone_intersect(const t_ray *ray, const t_cone *c,
		t_point3f *intersec)
{
	float	eq[3];
	float	t_sides[2];
	float	real_t;
	t_ray	r;
	float	a;

	a = c->radius * c->radius / (c->height * c->height);
	r = ray_to_referential(&c->ref, ray);
	eq[0] = r.direction.x * r.direction.x + r.direction.z * r.direction.z;
	eq[0] -= a * r.direction.y * r.direction.y;
	eq[1] = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
	eq[1] -= 2 * a * r.origin.y * r.direction.y;
	eq[2] = r.origin.x * r.origin.x + r.origin.z * r.origin.z;
	eq[2] -= a * r.origin.y * r.origin.y;
	solve_quadratic(eq[0], eq[1], eq[2], t_sides);
	real_t = check_height(&r, c, t_sides);
	if (real_t < 0.0f)
		return (0);
	r.origin = ray_at(0.99999f * real_t, &r);
	r = ray_from_referential(&c->ref, &r);
	*intersec = r.origin;
	return (1);
}
