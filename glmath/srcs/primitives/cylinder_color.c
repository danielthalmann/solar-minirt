/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trossel <trossel@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:06:41 by trossel           #+#    #+#             */
/*   Updated: 2022/06/14 10:15:50 by trossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glmath.h"

#define TS_PHI M_PI_4
#define TS_RHO 1.0f

float	cylinder_color_mask(const t_ray *normale, const t_cylinder *cyl)
{
	t_ray	r;
	float	phi;
	float	rho;
	float	mask;

	r = ray_to_referential(&cyl->ref, normale);
	rho = sqrt(r.origin.x * r.origin.x + r.origin.z * r.origin.z);
	phi = atan2f(r.origin.z, r.origin.x);
	mask = 1.0f;
	if (r.origin.y >= cyl->height || r.origin.y <= 0)
	{
		if ((fabsf(fmodf(phi + 1000, 2 * TS_PHI)) < TS_PHI
				&& fabsf(fmodf(rho + 1000, 2 * TS_RHO)) > TS_RHO)
			|| (fabsf(fmodf(phi + 1000, 2 * TS_PHI)) > TS_PHI
				&& fmodf(rho, 2 * TS_RHO) < TS_RHO))
			mask = 0.5f;
	}
	else if ((fabsf(fmodf(phi + 1000, 2 * TS_PHI)) < TS_PHI
			&& fabsf(fmodf(r.origin.y + 1000, 2 * TS_RHO)) < TS_RHO)
		|| (fabsf(fmodf(phi + 1000, 2 * TS_PHI)) > TS_PHI
			&& fmodf(r.origin.y, 2 * TS_RHO) > TS_RHO))
		mask = 0.5f;
	return (mask);
}

t_color	cylinder_color_normal(
	const t_ray *normale, const t_cylinder *cyl, float intensity)
{
	t_color	c;

	(void) normale;
	(void) cyl;
	(void) intensity;
	c = color_create_int(0);
	return (c);
}

t_color	cylinder_color_texture(
	const t_ray *normale, const t_cylinder *cyl, t_image *texture)
{
	t_color	c;

	(void) normale;
	(void) cyl;
	(void) texture;
	c = color_create_int(0);
	return (c);
}
