/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthalman <daniel@thalmann.li>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 10:26:45 by dthalman          #+#    #+#             */
/*   Updated: 2022/06/10 15:41:00 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

#include <stdio.h>

// static int	check_ends(t_ray *r, const t_cylinder *cyl, t_point3f *inter)
// {
// 	float	t_ends[2];
//
// 	if (fabsf(r->direction.y) < 1e-6)
// 		return (0);
// 	t_ends[0] = (0.0f - r->origin.y) / r->direction.y;
// 	t_ends[1] = (cyl->height - r->origin.y) / r->direction.y;
// 	return (0);
// }

// t_ends are the coefficients for the ray to reach the discs (actually planes)
// at the ends of the cylinder. t_ends[0] is the smallest of them.
//
static void	init_t_ends(t_ray *r, const t_cylinder *cyl, float *t_ends)
{
	float	tmp;

	t_ends[0] = -2.0f;
	t_ends[1] = -1.0f;
	if (fabsf(r->direction.y) > 1e-6)
	{
		t_ends[0] = (0.0f - r->origin.y) / r->direction.y;
		t_ends[1] = (cyl->height - r->origin.y) / r->direction.y;
	}
	if (t_ends[1] < t_ends[0])
	{
		tmp = t_ends[1];
		t_ends[1] = t_ends[0];
		t_ends[0] = tmp;
	}
}

// t_sides are the coefficients for the ray to reach the walls of the cylinder.
static float	check_height(t_ray *r, const t_cylinder *cyl, float t_sides[2])
{
	t_v3f	inters[2];
	float	t_ends[2];
	float	real_t;

	real_t = -1.0f;
	init_t_ends(r, cyl, t_ends);
	inters[0] = ray_at(t_sides[0], r);
	inters[1] = ray_at(t_sides[1], r);
	if (t_sides[0] >= 0 && inters[0].y >= 0 && inters[0].y <= cyl->height)
		real_t = t_sides[0];
	else if (t_ends[0] >= 0 && t_ends[0] > t_sides[0] && t_ends[0] < t_sides[1])
		real_t = t_ends[0];
	else if (t_ends[1] >= 0 && t_ends[1] > t_sides[0] && t_ends[1] < t_sides[1])
		real_t = t_ends[1];
	else if (t_sides[1] >= 0 && inters[1].y >= 0 && inters[1].y <= cyl->height)
		real_t = t_sides[1];
	return (real_t);
}

/* Used the formula described here:
 * https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html
 */
int	cylinder_intersect(const t_ray *ray, const t_cylinder *c,
		t_point3f *intersec)
{
	float	eq[3];
	float	t_sides[2];
	float	real_t;
	t_ray	r;

	r = ray_to_referential(&c->ref, ray);
	eq[0] = r.direction.x * r.direction.x + r.direction.z * r.direction.z;
	eq[1] = 2 * r.origin.x * r.direction.x + 2 * r.origin.z * r.direction.z;
	eq[2] = r.origin.x * r.origin.x + r.origin.z * r.origin.z
		- c->radius * c->radius;
	solve_quadratic(eq[0], eq[1], eq[2], t_sides);
	real_t = check_height(&r, c, t_sides);
	if (real_t < 0.0f)
		return (0);
	r.origin = ray_at(0.99999f * real_t, &r);
	r = ray_from_referential(&c->ref, &r);
	*intersec = r.origin;
	return (1);
}
